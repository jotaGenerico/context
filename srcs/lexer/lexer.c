/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:39 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:41 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		process_next_token(char *line, int *i, t_dlist **tokens);
t_token			*create_token(t_token_type type, char *value);

t_dlist	*lexer(char *line)
{
	t_dlist	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (process_next_token(line, &i, &tokens) == -1)
		{
			ft_dlstclear(&tokens, free_tokens);
			return (NULL);
		}
		if (!line[i])
			break ;
	}
	return (tokens);
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->was_quoted = 0;
	return (token);
}

t_token	*create_quoted_token(t_token_type type, char *value, int was_quoted)
{
	t_token	*token;

	token = create_token(type, value);
	if (!token)
		return (NULL);
	token->was_quoted = was_quoted;
	return (token);
}

static int	process_next_token(char *line, int *i, t_dlist **tokens)
{
	t_token	*new_token;

	skip_spaces(line, i);
	if (!line[*i])
		return (0);
	if (is_operator(line, *i))
		new_token = create_operator_token(line, i);
	else
		new_token = process_word_token(line, i);
	if (!new_token)
		return (-1);
	ft_dlstadd_back(tokens, ft_dlstnew(new_token));
	return (0);
}
