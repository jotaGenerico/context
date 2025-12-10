/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:47 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:49 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_sequence_node(t_ast *node, t_shell *shell);

int	execute_ast(t_ast *node, t_shell *shell)
{
	if (!node)
		return (1);
	if (node->type == NODE_COMMAND
		|| node->type == NODE_REDIR_IN
		|| node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND
		|| node->type == NODE_HEREDOC
		|| node->type == NODE_REDIR_ERR)
		return (exec_simple_cmd(node, shell));
	if (node->type == NODE_PIPE)
		return (exec_pipeline(node, shell));
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (exec_and_or(node, shell));
	if (node->type == NODE_SUBSHELL)
		return (exec_subshell(node, shell));
	if (node->type == NODE_SEQUENCE)
		return (exec_sequence_node(node, shell));
	return (1);
}

static int	exec_sequence_node(t_ast *node, t_shell *shell)
{
	execute_ast(node->left, shell);
	return (execute_ast(node->right, shell));
}
