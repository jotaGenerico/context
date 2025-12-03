/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:02:45 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 13:02:49 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*create_env_var(char *key_value_pair)
{
	t_env_var	*var;
	char		*equal_sign;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	equal_sign = ft_strchr(key_value_pair, '=');
	if (equal_sign)
	{
		var->key = ft_substr(key_value_pair, 0, equal_sign - key_value_pair);
		var->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		var->key = ft_strdup(key_value_pair);
		var->value = NULL;
	}
	if (!var->key || (equal_sign && !var->value))
	{
		free(var->key);
		free(var->value);
		free(var);
		return (NULL);
	}
	return (var);
}

void	free_env_var(void *content)
{
	t_env_var	*var;

	if (!content)
		return ;
	var = (t_env_var *)content;
	free(var->key);
	free(var->value);
	free(var);
}

void	init_shell(t_shell *shell, char **envp)
{
	int			i;
	t_env_var	*var;

	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->exit_status = 0;
	i = 0;
	while (envp && envp[i])
	{
		var = create_env_var(envp[i]);
		if (var)
			ft_dlstadd_back(&shell->env_list, ft_dlstnew(var));
		i++;
	}
}

void	cleanup_shell(t_shell *shell)
{
	if (shell->env_list)
		ft_dlstclear(&shell->env_list, free_env_var);
	if (shell->token_list)
		ft_dlstclear(&shell->token_list, free_tokens);
}
