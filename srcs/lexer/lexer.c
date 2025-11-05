#include "minishell.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

static char	*extract_word(char *line, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (line[*i] && !is_quote(line[*i]) && !is_operator(line, *i)
		&& line[*i] != ' ' && line[*i] != '\t')
		(*i)++;
	len = *i - start;
	word = ft_substr(line, start, len);
	return (word);
}

static t_token	*process_word_token(char *line, int *i)
{
	char	*word;

	if (is_quote(line[*i]))
		word = extract_quoted_word(line, i);
	else
		word = extract_word(line, i);
	if (!word)
		return (NULL);
	return (create_token(TOKEN_WORD, word));
}

t_dlist	*lexer(char *line)
{
	t_dlist	*tokens;
	t_token	*new_token;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (is_operator(line, i))
			new_token = create_operator_token(line, &i);
		else
			new_token = process_word_token(line, &i);
		if (!new_token)
		{
			ft_dlstclear(&tokens, free_tokens);
			return (NULL);
		}
		ft_dlstadd_back(&tokens, ft_dlstnew(new_token));
	}
	return (tokens);
}
