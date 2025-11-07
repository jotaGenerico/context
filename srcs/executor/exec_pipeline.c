#include "minishell.h"

static void	child_pipe_process(t_ast *node, t_shell *shell, int *pipe_fds, bool is_left)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (is_left)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 STDOUT pipe");
			exit(1);
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	else
	{
		if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		{
			perror("dup2 STDIN pipe");
			exit(1);
		}
		close(pipe_fds[1]);
		close(pipe_fds[0]);
	}

	execute_ast(node, shell);
	exit(shell->exit_status);
}

int	exec_pipe(t_ast *left, t_ast *right, t_shell *shell)
{
	int		pipe_fds[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_right;
	int		status_left;
	int		ret;

	signal(SIGINT, SIG_IGN);

	if (pipe(pipe_fds) == -1)
		return (perror("pipe"), 1);

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

	pid_right = fork();
	if (pid_right == -1)
	{
		perror("fork");
		close(pipe_fds[0]); close(pipe_fds[1]);
		waitpid(pid_left, NULL, 0);
		setup_signals();
		return (1);
	}
	if (pid_right == 0)
		child_pipe_process(right, shell, pipe_fds, false);

	close(pipe_fds[0]);
	close(pipe_fds[1]);

	waitpid(pid_right, &status_right, 0);
	waitpid(pid_left, &status_left, 0);

	setup_signals();

	if (WIFEXITED(status_right))
		ret = WEXITSTATUS(status_right);
	else if (WIFSIGNALED(status_right))
		ret = 128 + WTERMSIG(status_right);
	else
		ret = 1;

	return (ret);
}

int	exec_pipeline(t_ast *node, t_shell *shell)
{
	if (!node || node->type != NODE_PIPE)
		return (1);
	shell->exit_status = exec_pipe(node->left, node->right, shell);
	return (shell->exit_status);
}
