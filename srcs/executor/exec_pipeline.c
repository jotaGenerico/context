#include "minishell.h"

// FUNÇÃO 1/3: Roda o processo filho (executando um lado do pipe)
static void	child_pipe_process(t_ast *node, t_shell *shell, int *pipe_fds, bool is_left)
{
    // Restaura sinais para o padrão (crítico)
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

	if (is_left)
	{
		// Lado Esquerdo (Writer): Redireciona STDOUT para a escrita (1)
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
        {
			perror("dup2 STDOUT pipe");
            exit(1);
        }
		close(pipe_fds[0]); // Fecha o lado de leitura
		close(pipe_fds[1]); // Fecha a cópia do FD original
	}
	else
	{
		// Lado Direito (Reader): Redireciona STDIN para a leitura (0)
		if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
        {
			perror("dup2 STDIN pipe");
            exit(1);
        }
		close(pipe_fds[1]); // Fecha o lado de escrita
		close(pipe_fds[0]); // Fecha a cópia do FD original
	}

	execute_ast(node, shell);
	exit(shell->exit_status);
}

// FUNÇÃO 2/3: Função principal de execução de pipeline

int	exec_pipe(t_ast *left, t_ast *right, t_shell *shell)
{
	int		pipe_fds[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_right; // Status do comando mais à direita (o que deve ser retornado)
	int		status_left;
	int		ret;

	// O pai deve ignorar SIGINT durante a execução dos filhos.
	signal(SIGINT, SIG_IGN);

	if (pipe(pipe_fds) == -1)
		return (perror("pipe"), 1);

	// 1. Processo da Esquerda (PIPE WRITE)
	pid_left = fork();
	if (pid_left == -1)
	{
		perror("fork");
		close(pipe_fds[0]); close(pipe_fds[1]);
		setup_signals();
		return (1);
	}
	if (pid_left == 0)
		child_pipe_process(left, shell, pipe_fds, true);

	// 2. Processo da Direita (PIPE READ)
	pid_right = fork();
	if (pid_right == -1)
	{
		perror("fork");
		// Em caso de falha, fecha os pipes e espera o primeiro filho (pid_left)
		close(pipe_fds[0]); close(pipe_fds[1]);
		waitpid(pid_left, NULL, 0);
		setup_signals();
		return (1);
	}
	if (pid_right == 0)
		child_pipe_process(right, shell, pipe_fds, false);

	// 3. PAI: FECHAMENTO DE FDs e WAITPID
	// CORREÇÃO CRÍTICA DO HANG: FECHAR AMBOS FDs NO PAI.
	close(pipe_fds[0]); // Fecha o lado de leitura no PAI
	close(pipe_fds[1]); // Fecha o lado de escrita no PAI (LIBERA wc -L!)

	// Espera os dois filhos. O status do último comando (direita) é o que importa.
	waitpid(pid_right, &status_right, 0);
	waitpid(pid_left, &status_left, 0);

	setup_signals(); // Restaura o handler de SIGINT (readline)

	// Retorna o status de saída do ÚLTIMO comando da pipeline.
	if (WIFEXITED(status_right))
		ret = WEXITSTATUS(status_right);
	else if (WIFSIGNALED(status_right))
		ret = 128 + WTERMSIG(status_right);
	else
		ret = 1; // Erro genérico

	return (ret);
}


// FUNÇÃO 3/3: Ponto de entrada
int	exec_pipeline(t_ast *node, t_shell *shell)
{
	if (!node || node->type != NODE_PIPE)
		return (1);
	shell->exit_status = exec_pipe(node->left, node->right, shell);
	return (shell->exit_status);
}
