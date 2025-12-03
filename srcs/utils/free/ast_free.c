/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:02:35 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:02:37 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_ast_content(t_ast *node);

void	ast_free(t_ast *node)
{
	if (!node)
		return ;
	ast_free(node->left);
	ast_free(node->right);
	free_ast_content(node);
	free(node);
}

static void	free_ast_content(t_ast *node)
{
	if (!node)
		return ;
	if (node->argv)
		free_char_array(node->argv);
	if (node->argv_quoted)
		free(node->argv_quoted);
	if (node->filename)
		free(node->filename);
	if (node->type == NODE_HEREDOC && node->heredoc_fd != -1)
		safe_close(node->heredoc_fd);
}
