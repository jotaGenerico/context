/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:03:08 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:03:10 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		create_new_var(t_dlist **env_list, char *assignment);
static int		update_existing_var(t_dlist *node, char *new_value);
static t_dlist	*find_env_var(t_dlist *list, char *key);

char	*get_env_value(char *key, t_shell *shell)
{
	t_dlist		*curr;
	t_env_var	*var;

	curr = shell->env_list;
	while (curr)
	{
		var = curr->content;
		if (ft_strcmp(var->key, key) == 0)
			return (var->value);
		curr = curr->next;
	}
	return (NULL);
}

int	env_list_set_var(t_dlist **env_list, char *assignment)
{
	char		*equal_sign;
	char		*key;
	t_dlist		*node;
	int			status;

	equal_sign = ft_strchr(assignment, '=');
	if (!equal_sign)
		return (1);
	key = ft_substr(assignment, 0, equal_sign - assignment);
	if (!key)
		return (1);
	node = find_env_var(*env_list, key);
	free(key);
	if (node)
		status = update_existing_var(node, equal_sign + 1);
	else
		status = create_new_var(env_list, assignment);
	return (status);
}

static int	create_new_var(t_dlist **env_list, char *assignment)
{
	t_env_var	*new_var;

	new_var = create_env_var(assignment);
	if (!new_var)
		return (1);
	ft_dlstadd_back(env_list, ft_dlstnew(new_var));
	return (0);
}

static int	update_existing_var(t_dlist *node, char *new_value)
{
	t_env_var	*var;
	char		*old_value;

	var = (t_env_var *)node->content;
	old_value = var->value;
	var->value = ft_strdup(new_value);
	if (!var->value)
	{
		var->value = old_value;
		return (1);
	}
	if (old_value)
		free(old_value);
	return (0);
}

static t_dlist	*find_env_var(t_dlist *list, char *key)
{
	t_dlist		*curr;
	t_env_var	*var;

	curr = list;
	while (curr)
	{
		var = (t_env_var *)curr->content;
		if (ft_strcmp(var->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
