/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:59:42 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 15:59:44 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_and_or(t_ast *node, t_shell *shell)
{
	int	left_status;

	left_status = execute_ast(node->left, shell);
	shell->exit_status = left_status;
	if (node->type == NODE_AND && left_status == 0)
	{
		shell->exit_status = execute_ast(node->right, shell);
		return (shell->exit_status);
	}
	else if (node->type == NODE_OR && left_status != 0)
	{
		shell->exit_status = execute_ast(node->right, shell);
		return (shell->exit_status);
	}
	return (left_status);
}
