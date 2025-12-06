/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:13 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:15 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:13 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/06 00:00:00 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc_input(t_ast *node);
static int	handle_eof_heredoc(t_ast *node, int *pipe_fds);
static int	process_heredoc_loop(t_ast *node, int write_fd);

int	handle_heredocs(t_ast *node, t_shell *shell)
{
	int	result;

	if (!node)
		return (0);
	if (node->type == NODE_HEREDOC)
	{
		result = read_heredoc_input(node);
		if (result == 130)
		{
			shell->exit_status = 130;
			return (130);
		}
		if (result != 0)
			return (1);
	}
	result = handle_heredocs(node->left, shell);
	if (result != 0)
		return (result);
	result = handle_heredocs(node->right, shell);
	return (result);
}

static int	handle_eof_heredoc(t_ast *node, int *pipe_fds)
{
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "minishell: warning: here-document ", 34);
	write(STDOUT_FILENO, "delimited by end-of-file (wanted `", 35);
	write(STDOUT_FILENO, node->filename, ft_strlen(node->filename));
	write(STDOUT_FILENO, "')\n", 3);
	close(pipe_fds[1]);
	node->heredoc_fd = pipe_fds[0];
	setup_signals();
	return (0);
}

static int	process_heredoc_loop(t_ast *node, int write_fd)
{
	char	*line;

	while (1)
	{
		if (g_signal == SIGINT)
			return (1);
		write(STDOUT_FILENO, "> ", 2);
		line = read_heredoc_line();
		if (!line)
		{
			if (g_signal == SIGINT)
				return (1);
			return (2);
		}
		if (process_heredoc_line(line, node, write_fd))
			break ;
	}
	return (0);
}

static int	read_heredoc_input(t_ast *node)
{
	int	pipe_fds[2];
	int	result;

	if (pipe(pipe_fds) == -1)
		return (perror("pipe"), 1);
	g_signal = 0;
	setup_heredoc_signals();
	result = process_heredoc_loop(node, pipe_fds[1]);
	if (result == 1)
		return (handle_heredoc_interrupt(pipe_fds));
	if (result == 2)
		return (handle_eof_heredoc(node, pipe_fds));
	close(pipe_fds[1]);
	node->heredoc_fd = pipe_fds[0];
	setup_signals();
	return (0);
}
