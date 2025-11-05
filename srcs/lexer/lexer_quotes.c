#include "minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
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

char	*extract_quoted_word(char *line, int *i)
{
	char	quote;
	int		end;
	char	*content;
	int		start; // Adicionada a variável de início

	start = *i; // Marca o início, incluindo a aspa
	quote = line[*i];
	end = find_closing_quote(line, *i, quote);
	if (end == -1)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}
	// CORREÇÃO CRÍTICA: Substr agora INCLUI as aspas
	// Pega do índice 'start' (aspas de abertura) até 'end' (aspas de fechamento)
	content = ft_substr(line, start, end - start + 1);
	*i = end + 1;
	return (content);
}
