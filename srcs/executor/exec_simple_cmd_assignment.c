/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd_assignment.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:27 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:28 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_key(char *assignment);
static int	is_valid_key_char(char c);

int	handle_assignment_only(t_ast *node, t_shell *shell)
{
	char	*assignment;

	if (!node->argv || node->argv[1] != NULL)
		return (0);
	assignment = node->argv[0];
	if (ft_strchr(assignment, '=') == NULL)
		return (0);
	if (validate_key(assignment) == 0)
		return (0);
	if (env_list_set_var(&(shell->env_list), assignment) == 0)
	{
		shell->exit_status = 0;
		return (1);
	}
	return (0);
}

static int	is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static int	validate_key(char *assignment)
{
	int	i;

	i = 0;
	if (!ft_isalpha(assignment[i]) && assignment[i] != '_')
		return (0);
	i++;
	while (assignment[i] && assignment[i] != '=')
	{
		if (!is_valid_key_char(assignment[i]))
			return (0);
		i++;
	}
	return (1);
}
