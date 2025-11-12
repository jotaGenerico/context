#include "minishell.h"

static char	*append_word_part(char *line, int *i, char *full_word);

t_token	*process_word_token(char *line, int *i)
{
	char	*full_word;

	full_word = ft_strdup("");
	if (!full_word)
		return (NULL);
	while (line[*i] && !ft_isspace(line[*i]) && !is_operator(line, *i))
	{
		full_word = append_word_part(line, i, full_word);
		if (!full_word)
			return (NULL);
	}
	if (ft_strlen(full_word) == 0)
	{
		free(full_word);
		return (NULL);
	}
	return (create_token(TOKEN_WORD, full_word));
}

static char	*append_word_part(char *line, int *i, char *full_word)
{
	char	*part;

	if (is_quote(line[*i]))
		part = extract_quoted_word(line, i);
	else
		part = extract_word(line, i);
	if (!part)
	{
		free(full_word);
		return (NULL);
	}
	full_word = ft_strjoin_free(full_word, part);
	free(part);
	return (full_word);
}
