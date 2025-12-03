/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:01:26 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 16:01:28 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_closing_quote(char *line, int start, char quote);

char	*extract_quoted_word(char *line, int *i)
{
	char	quote;
	int		end;
	char	*content;
	int		start;

	start = *i;
	quote = line[*i];
	end = find_closing_quote(line, *i, quote);
	if (end == -1)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}
	content = ft_substr(line, start, end - start + 1);
	*i = end + 1;
	return (content);
}

static int	find_closing_quote(char *line, int start, char quote)
{
	int	i;

	i = start + 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}
