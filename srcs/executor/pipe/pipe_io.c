/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:06:29 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/04 15:06:31 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe_output(t_shell *shell, int *pipe_fds)
{
	close(pipe_fds[0]);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 STDOUT pipe");
		close(pipe_fds[1]);
		clean_exit_child(shell, 1);
	}
	close(pipe_fds[1]);
}

void	setup_pipe_input(t_shell *shell, int *pipe_fds)
{
	close(pipe_fds[1]);
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2 STDIN pipe");
		close(pipe_fds[0]);
		clean_exit_child(shell, 1);
	}
	close(pipe_fds[0]);
}
