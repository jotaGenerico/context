/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:03:47 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:03:48 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote_char(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '"'))
	{
		*quote_char = c;
		*in_quote = 1;
		return (1);
	}
	if (*in_quote && c == *quote_char)
	{
		*in_quote = 0;
		*quote_char = 0;
		return (1);
	}
	return (0);
}

char	*process_filename(char *raw_filename)
{
	char	*result;
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;

	result = malloc(ft_strlen(raw_filename) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (raw_filename[i])
	{
		if (!handle_quote_char(raw_filename[i], &in_quote, &quote_char))
			result[j++] = raw_filename[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_ast	*create_redir_node(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (ast_new_node(NODE_REDIR_IN, NULL, NULL));
	else if (type == TOKEN_REDIR_OUT)
		return (ast_new_node(NODE_REDIR_OUT, NULL, NULL));
	else if (type == TOKEN_REDIR_APPEND)
		return (ast_new_node(NODE_REDIR_APPEND, NULL, NULL));
	else
		return (ast_new_node(NODE_HEREDOC, NULL, NULL));
}
