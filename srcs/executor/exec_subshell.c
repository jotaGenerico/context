/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:37 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:38 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_subshell(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		setup_signals();
		return (perror("fork"), 1);
	}
	if (pid == 0)
	{
		setup_signals_child();
		execute_ast(node->left, shell);
		clean_exit_child(shell, shell->exit_status);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (shell->exit_status);
}
