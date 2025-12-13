/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:03:39 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:03:40 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_operator(char *line, int i)
{
	if (line[i] == '|' || line[i] == '<' || line[i] == '>'
		|| line[i] == '(' || line[i] == ')' || line[i] == '&')
		return (1);
	if (line[i] == '2' && line[i + 1] == '>')
		return (1);
	return (0);
}

char	*extract_word(char *line, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (line[*i] && !is_quote(line[*i]) && !is_operator(line, *i)
		&& !ft_isspace(line[*i]))
		(*i)++;
	len = *i - start;
	word = ft_substr(line, start, len);
	return (word);
}
