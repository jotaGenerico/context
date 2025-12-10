/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:58:52 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 15:58:53 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_infile(t_ast *node);
static int	apply_heredoc(t_ast *node);
static int	apply_node_redirection(t_ast *node);

int	apply_redirections(t_ast *node, t_shell *shell)
{
	int	status;

	(void)shell;
	if (!node)
		return (0);
	if (node->left)
	{
		if (apply_redirections(node->left, shell) != 0)
			return (1);
	}
	status = apply_node_redirection(node);
	if (node->right && status == 0)
		status = apply_redirections(node->right, shell);
	return (status);
}

static int	apply_node_redirection(t_ast *node)
{
	if (node->type == NODE_REDIR_IN)
		return (open_infile(node));
	else if (node->type == NODE_REDIR_OUT)
		return (open_outfile_trunc(node));
	else if (node->type == NODE_REDIR_APPEND)
		return (open_outfile_append(node));
	else if (node->type == NODE_HEREDOC)
		return (apply_heredoc(node));
	else if (node->type == NODE_REDIR_ERR)
		return (open_errfile_trunc(node));
	return (0);
}

static int	apply_heredoc(t_ast *node)
{
	if (node->heredoc_fd < 0)
	{
		ft_dprintf(2, "minishell: internal heredoc error (invalid fd)\n");
		return (-1);
	}
	if (dup2(node->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(node->heredoc_fd);
		return (-1);
	}
	close(node->heredoc_fd);
	return (0);
}

static int	open_infile(t_ast *node)
{
	int		fd;
	char	*clean_filename;

	clean_filename = process_filename(node->filename);
	if (!clean_filename)
		return (-1);
	fd = open(clean_filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(clean_filename);
		free(clean_filename);
		return (-1);
	}
	free(clean_filename);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
