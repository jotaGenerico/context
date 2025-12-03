/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:02:56 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:02:57 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	split_export_arg(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*key = ft_substr(arg, 0, eq - arg);
		*value = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

static int	process_one_export(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;

	split_export_arg(arg, &key, &value);
	if (!is_valid_identifier(key))
	{
		ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
		free(key);
		if (value)
			free(value);
		return (1);
	}
	if (value)
	{
		set_env_var(shell, key, value);
		free(value);
	}
	else
	{
		if (!get_env_value(key, shell))
			set_env_var(shell, key, "");
	}
	free(key);
	return (0);
}

int	process_exports(char **argv, t_shell *shell)
{
	int	i;
	int	status;
	int	last_error;

	i = 1;
	last_error = 0;
	while (argv[i])
	{
		status = process_one_export(shell, argv[i]);
		if (status != 0)
			last_error = status;
		i++;
	}
	return (last_error);
}

int	builtin_export(char **argv, t_shell *shell)
{
	if (!argv[1])
		return (print_all_env(shell));
	return (process_exports(argv, shell));
}
