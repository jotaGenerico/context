/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:19 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:21 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fds_except_std(void)
{
	int	fd;

	fd = 3;
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}

void	close_custom_redirs(t_ast *node)
{
	if (!node)
		return ;
	if (node->left)
		close_custom_redirs(node->left);
	if (node->right)
		close_custom_redirs(node->right);
	if ((node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_APPEND
			|| node->type == NODE_REDIR_IN) && node->fd_target > 2)
	{
		close(node->fd_target);
	}
}
