/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:57:44 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 15:57:47 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			create_new_var(t_shell *shell, char *key, char *value);
static void			update_existing_var(t_env_var *var, char *value);
static t_env_var	*find_env_var(t_shell *shell, const char *key);

void	set_env_var(t_shell *shell, char *key, char *value)
{
	t_env_var	*var;

	var = find_env_var(shell, key);
	if (var)
		update_existing_var(var, value);
	else
		create_new_var(shell, key, value);
}

int	print_all_env(t_shell *shell)
{
	t_dlist		*lst;
	t_env_var	*var;

	lst = shell->env_list;
	while (lst)
	{
		var = lst->content;
		ft_printf("declare -x %s=\"%s\"\n", var->key, var->value);
		lst = lst->next;
	}
	return (0);
}

static t_env_var	*find_env_var(t_shell *shell, const char *key)
{
	t_dlist		*lst;
	t_env_var	*var;

	lst = shell->env_list;
	while (lst)
	{
		var = lst->content;
		if (ft_strcmp(var->key, key) == 0)
			return (var);
		lst = lst->next;
	}
	return (NULL);
}

static void	update_existing_var(t_env_var *var, char *value)
{
	free(var->value);
	var->value = ft_strdup(value);
}

static void	create_new_var(t_shell *shell, char *key, char *value)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	ft_dlstadd_back(&shell->env_list, ft_dlstnew(new));
}
