/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:58:20 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 15:58:22 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_shell *shell)
{
	int			i;
	t_dlist		*lst;
	t_dlist		*next;
	t_env_var	*var;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		lst = shell->env_list;
		while (lst)
		{
			next = lst->next;
			var = lst->content;
			if (ft_strcmp(var->key, argv[i]) == 0)
			{
				ft_dlstremove(&shell->env_list, lst, free_env_var);
				break ;
			}
			lst = next;
		}
		i++;
	}
	return (0);
}
