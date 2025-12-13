/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:57:28 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 15:57:31 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	t_dlist		*lst;
	t_env_var	*var;

	lst = shell->env_list;
	while (lst)
	{
		var = lst->content;
		if (var->value)
			ft_printf("%s=%s\n", var->key, var->value);
		lst = lst->next;
	}
	return (0);
}
