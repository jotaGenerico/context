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

static void		child_pipe_process(t_ast *node, t_shell *shell, int *pipe_fds,
					int is_left);
static pid_t	fork_left_child(t_ast *left, t_shell *shell, int *pipe_fds,
					int exit_status_left);

int	exec_pipeline(t_ast *node, t_shell *shell)
{
	if (!node || node->type != NODE_PIPE)
		return (1);
	shell->exit_status = exec_pipe(node->left, node->right, shell);
	return (shell->exit_status);
}

int	exec_pipe(t_ast *left, t_ast *right, t_shell *shell)
{
	int		pipe_fds[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		exit_status_left;

	exit_status_left = handle_left_builtin(left, shell);
	if (exit_status_left > 0)
		return (exit_status_left);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fds) == -1)
		return (perror("pipe"), 1);
	pid_left = fork_left_child(left, shell, pipe_fds, exit_status_left);
	if (pid_left == -1)
		return (1);
	pid_right = fork();
	if (pid_right == -1)
		return (handle_fork_error(pipe_fds, pid_left));
	if (pid_right == 0)
		child_pipe_process(right, shell, pipe_fds, 0);
	return (parent_wait_and_close(pid_left, pid_right, pipe_fds));
}

static void	child_pipe_process(t_ast *node, t_shell *shell, int *pipe_fds,
		int is_left)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_left)
		setup_pipe_output(shell, pipe_fds);
	else
		setup_pipe_input(shell, pipe_fds);
	execute_ast(node, shell);
	clean_exit_child(shell, shell->exit_status);
}

static pid_t	fork_left_child(t_ast *left, t_shell *shell, int *pipe_fds,
		int exit_status_left)
{
	pid_t	pid_left;

	pid_left = fork();
	if (pid_left == -1)
		return (handle_fork_error(pipe_fds, 0), -1);
	if (pid_left == 0)
	{
		if (left->type == NODE_COMMAND && is_state_changing_builtin(left))
			clean_exit_child(shell, exit_status_left);
		child_pipe_process(left, shell, pipe_fds, 1);
	}
	return (pid_left);
}
