/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:13 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/06 00:39:15 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_interrupt(int *pipe_fds)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	setup_signals();
	return (130);
}

int	process_heredoc_line(char *line, t_ast *node, int write_fd, t_shell *shell)
{
	size_t	len_line;
	size_t	len_delim;
	char	*expanded_line;

	len_line = ft_strlen(line);
	len_delim = ft_strlen(node->filename);
	if (ft_strncmp(line, node->filename, len_delim + 1) == 0
		&& len_line == len_delim)
	{
		free(line);
		return (1);
	}
	if (node->heredoc_expand)
		expanded_line = expand_word(line, shell);
	else
		expanded_line = line;
	ft_putendl_fd(expanded_line, write_fd);
	if (node->heredoc_expand)
		free(expanded_line);
	free(line);
	return (0);
}

char	*read_heredoc_line(void)
{
	char	buffer[1024];
	char	ch;
	int		i;
	int		bytes_read;

	i = 0;
	while (i < 1023)
	{
		bytes_read = read(STDIN_FILENO, &ch, 1);
		if (bytes_read <= 0)
		{
			if (i == 0)
				return (NULL);
			break ;
		}
		if (ch == '\n')
			break ;
		buffer[i++] = ch;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}
