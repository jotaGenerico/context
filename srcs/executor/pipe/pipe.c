#include "minishell.h"

extern char **environ;

/* Configura sinais padrão para o filho */
static void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/* -------------------------------------------------------------------------- */
/* Executa o comando dentro do processo filho */
static void	child_exec(t_ast *cmd, int i, int n, int *pipes, t_shell *shell)
{
	char	*path;
	char	**env_array; // Novo vetor de ambiente

	// 1. Redirecionamento de Pipe de ENTRADA (leitura)
	if (i > 0)
	{
		if (dup2(pipes[2 * (i - 1)], STDIN_FILENO) == -1)
		{
			perror("dup2"); // CORREÇÃO 1: Separa perror e exit
			exit(1);
		}
	}
	// 2. Redirecionamento de Pipe de SAÍDA (escrita)
	if (i < n - 1)
	{
		if (dup2(pipes[2 * i + 1], STDOUT_FILENO) == -1)
		{
			perror("dup2"); // CORREÇÃO 1: Separa perror e exit
			exit(1);
		}
	}

	close_all_pipes(pipes, n - 1); // Fecha todos os FDs de pipe herdados
	child_signals(); // Restaura sinais para padrão (para interrupção)

	// 3. Aplica redirecionamentos de arquivo (deve retornar int e ser checado)
	if (apply_redirections(cmd, shell) != 0)
		exit(1); // Sai com status 1 se redirecionamento falhar (ex: file not found)

	// 4. Execução do Builtin (dentro do processo filho)
	if (is_builtin(cmd))
		exit(exec_builtin_child(cmd, shell));

	// 5. Execução do Comando Externo
	path = find_command_path(cmd->argv[0], shell);
	if (!path)
	{
		// CORREÇÃO 2: Substituir ft_dprintf por ft_putstr_fd/ft_putendl_fd
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127); // 127: Command not found
	}

	// 6. Prepara e executa com ambiente gerenciado
	env_array = env_list_to_array(shell->env_list); // Função de conversão
	execve(path, cmd->argv, env_array); // CORREÇÃO 3: Passa o seu ambiente

	// Se execve falhar (ex: permissão negada, mas caminho encontrado)
	perror("execve");
	free_char_array(env_array); // Libera o array antes de sair
	exit(126); // 126: Command invoked cannot execute
}

/* -------------------------------------------------------------------------- */
/* Função principal da pipeline: cria pipes, forks e espera filhos */
int	run_pipeline(t_ast **cmds, int n, t_shell *shell)
{
	int		*pipes;
	pid_t	*pids;
	int		i;
	int		ret;

	if (n <= 0)
		return (1);
	if (n == 1)
		return (execute_ast(cmds[0], shell)); // Executa como comando simples

	pipes = alloc_pipes(n - 1); // Aloca n-1 pares de pipes
	if (!pipes)
		return (ft_putendl_fd("minishell: pipe error", 2), 1);
	pids = alloc_pids(n);
	if (!pids)
		return (free_pipes(pipes, n - 1), perror("malloc"), 1);

	i = 0;
	while (i < n)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			break ;
		}
		if (pids[i] == 0)
			child_exec(cmds[i], i, n, pipes, shell);
		i++;
	}

	free_pipes(pipes, n - 1); // Pai fecha todos os pipes
	ret = wait_for_children(pids, i, shell); // Pai espera pelos filhos
	free(pids);
	return (ret);
}
