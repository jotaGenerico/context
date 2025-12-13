/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:59:48 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 15:59:51 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_ast *node, t_shell *shell)
{
	if (ft_strcmp(node->argv[0], "cd") == 0)
		return (builtin_cd(node->argv, shell));
	else if (ft_strcmp(node->argv[0], "echo") == 0)
		return (builtin_echo(node->argv));
	else if (ft_strcmp(node->argv[0], "env") == 0)
	{
		if (node->argv[1] != NULL)
		{
			ft_dprintf(2, "minishell: env: argumentos demais\n");
			return (1);
		}
		return (builtin_env(shell));
	}
	else if (ft_strcmp(node->argv[0], "exit") == 0)
		return (builtin_exit(node, shell));
	else if (ft_strcmp(node->argv[0], "export") == 0)
		return (builtin_export(node->argv, shell));
	else if (ft_strcmp(node->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(node->argv[0], "unset") == 0)
		return (builtin_unset(node->argv, shell));
	return (1);
}
