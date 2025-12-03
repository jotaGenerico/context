/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:20 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:22 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_pipe_and_semicolon_type(char *line, int *i);
static t_token_type	get_operator_type(char *line, int *i);
static t_token_type	get_redir_and_paren_type(char *line, int *i);

t_token	*create_operator_token(char *line, int *i)
{
	t_token_type	type;
	char			*value;
	int				start;

	start = *i;
	type = get_operator_type(line, i);
	if (type == TOKEN_ERROR)
		return (NULL);
	(*i)++;
	value = ft_substr(line, start, *i - start);
	if (!value)
		return (NULL);
	return (create_token(type, value));
}

static t_token_type	get_redir_and_paren_type(char *line, int *i)
{
	if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			(*i)++;
			return (TOKEN_HEREDOC);
		}
		return (TOKEN_REDIR_IN);
	}
	if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			(*i)++;
			return (TOKEN_REDIR_APPEND);
		}
		return (TOKEN_REDIR_OUT);
	}
	if (line[*i] == '(')
		return (TOKEN_LPAREN);
	if (line[*i] == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_ERROR);
}

static t_token_type	get_operator_type(char *line, int *i)
{
	t_token_type	type;

	type = get_pipe_and_semicolon_type(line, i);
	if (type != TOKEN_ERROR)
		return (type);
	if (line[*i] == '&')
	{
		if (line[*i + 1] == '&')
		{
			(*i)++;
			return (TOKEN_AND);
		}
		ft_putendl_fd("minishell: syntax error near unexpected token '&'", 2);
		return (TOKEN_ERROR);
	}
	return (get_redir_and_paren_type(line, i));
}

static t_token_type	get_pipe_and_semicolon_type(char *line, int *i)
{
	if (line[*i] == '|')
	{
		if (line[*i + 1] == '|')
		{
			(*i)++;
			return (TOKEN_OR);
		}
		return (TOKEN_PIPE);
	}
	return (TOKEN_ERROR);
}
