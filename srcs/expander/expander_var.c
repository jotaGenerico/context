/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:00 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:01 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_exit_status(t_shell *shell);

char	*expand_variable(char *word, int *i, t_shell *shell)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*expanded;

	(*i)++;
	if (word[*i] == '?')
	{
		(*i)++;
		return (get_exit_status(shell));
	}
	var_len = get_var_name_len(&word[*i]);
	if (var_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(word, *i, var_len);
	if (!var_name)
		return (NULL);
	*i += var_len;
	var_value = get_env_value(var_name, shell);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	expanded = ft_strdup(var_value);
	return (expanded);
}

static char	*get_exit_status(t_shell *shell)
{
	return (ft_itoa(shell->exit_status));
}
