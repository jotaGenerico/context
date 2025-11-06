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
	char	**env_array;

	/* 1. Redirecionamento de Pipe de ENTRADA */
	if (i > 0 && dup2(pipes[2 * (i - 1)], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}

	/* 2. Redirecionamento de Pipe de SAÍDA */
	if (i < n - 1 && dup2(pipes[2 * i + 1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}

	close_all_pipes(pipes, n - 1);
	child_signals();

	/* 3. Aplica redirecionamentos */
	if (apply_redirections(cmd, shell) != 0)
		exit(1);

	/* 4. Executa Builtin */
	if (is_builtin(cmd))
		exit(exec_builtin_child(cmd, shell));

	/* 5. Executa Comando Externo */
	path = find_command_path(cmd->argv[0], shell);
	if (!path)
	{
		if (ft_strchr(cmd->argv[0], '/'))
		{
			if (access(cmd->argv[0], F_OK) == 0)
			{
				if (is_directory(cmd->argv[0]))
				{
					ft_dprintf(2, "minishell: %s: Is a directory\n",
						cmd->argv[0]);
					exit(126);
				}
				if (access(cmd->argv[0], X_OK) != 0)
				{
					ft_dprintf(2, "minishell: %s: Permission denied\n",
						cmd->argv[0]);
					exit(126);
				}
				/* Existe, mas não é um executável válido */
				ft_dprintf(2, "minishell: %s: command not found\n",
					cmd->argv[0]);
				exit(127);
			}
			ft_dprintf(2, "minishell: %s: No such file or directory\n",
				cmd->argv[0]);
			exit(127);
		}
		ft_dprintf(2, "minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}

	/* 6. Executa com ambiente */
	env_array = env_list_to_array(shell->env_list);
	execve(path, cmd->argv, env_array);

	/* 7. Se execve falhar */
	perror("execve");
	free_char_array(env_array);
	free(path);
	exit(126);
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
