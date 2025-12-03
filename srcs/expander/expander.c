/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:14 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:16 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_dlist *tokens, t_shell *shell)
{
	t_dlist	*current;
	t_token	*token;
	char	*expanded;

	current = tokens;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == TOKEN_WORD)
		{
			expanded = expand_word(token->value, shell);
			if (expanded)
			{
				free(token->value);
				token->value = expanded;
			}
		}
		current = current->next;
	}
}

void	expand_variables(char **argv, t_shell *shell)
{
	int		i;
	char	*expanded_word;

	i = 0;
	while (argv[i])
	{
		expanded_word = expand_word(argv[i], shell);
		if (!expanded_word)
			return ;
		free(argv[i]);
		argv[i] = expanded_word;
		i++;
	}
}
