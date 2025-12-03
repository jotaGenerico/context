/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:19 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:21 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pipe_process(t_ast *node, t_shell *shell, int *pipe_fds,
				int is_left);
static int	handle_fork_error(int *pipe_fds, pid_t pid_to_wait);
static int	parent_wait_and_close(pid_t pid_left, pid_t pid_right,
				int *pipe_fds);

int	exec_pipe(t_ast *left, t_ast *right, t_shell *shell)
{
	int		pipe_fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	signal(SIGINT, SIG_IGN);
	if (pipe(pipe_fds) == -1)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (pid_left == -1)
		return (handle_fork_error(pipe_fds, 0));
	if (pid_left == 0)
		child_pipe_process(left, shell, pipe_fds, 1);
	pid_right = fork();
	if (pid_right == -1)
		return (handle_fork_error(pipe_fds, pid_left));
	if (pid_right == 0)
		child_pipe_process(right, shell, pipe_fds, 0);
	return (parent_wait_and_close(pid_left, pid_right, pipe_fds));
}

int	exec_pipeline(t_ast *node, t_shell *shell)
{
	if (!node || node->type != NODE_PIPE)
		return (1);
	shell->exit_status = exec_pipe(node->left, node->right, shell);
	return (shell->exit_status);
}

static void	child_pipe_process(t_ast *node, t_shell *shell, int *pipe_fds,
		int is_left)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_high_fds_except_pipe();
	if (is_left)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 STDOUT pipe");
			clean_exit_child(shell, 1);
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	else
	{
		if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		{
			perror("dup2 STDIN pipe");
			clean_exit_child(shell, 1);
		}
		close(pipe_fds[1]);
		close(pipe_fds[0]);
	}
	execute_ast(node, shell);
	clean_exit_child(shell, shell->exit_status);
}

static int	handle_fork_error(int *pipe_fds, pid_t pid_to_wait)
{
	perror("fork");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	if (pid_to_wait > 0)
		waitpid(pid_to_wait, NULL, 0);
	setup_signals();
	return (1);
}

static int	parent_wait_and_close(pid_t pid_left, pid_t pid_right,
		int *pipe_fds)
{
	int	status_right;
	int	status_left;
	int	ret;

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
