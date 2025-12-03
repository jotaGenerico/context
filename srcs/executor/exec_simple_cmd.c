/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:31 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:33 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_simple_cmd(t_ast *node, t_shell *shell)
{
	t_ast	*cmd_node;

	if (!node)
		return (1);
	cmd_node = get_command_node(node);
	if (has_redirections(node) && (!cmd_node || !cmd_node->argv
			|| !cmd_node->argv[0]))
		return (handle_redirect_only(node, shell));
	if (!cmd_node || !cmd_node->argv || !cmd_node->argv[0])
		return (0);
	expand_variables(cmd_node->argv, shell);
	cmd_node->argv = remove_empty_args(cmd_node->argv);
	if (is_empty_command(cmd_node->argv))
		return (handle_empty_after_expand(node, shell, cmd_node));
	if (should_expand_wildcards(cmd_node->argv, cmd_node->argv_quoted))
	{
		if (expand_wildcards(&(cmd_node->argv)) != 0)
		{
			shell->exit_status = 1;
			return (shell->exit_status);
		}
	}
	if (is_empty_command(cmd_node->argv))
		return (handle_empty_after_expand(node, shell, cmd_node));
	return (process_command(node, shell, cmd_node));
}
