#include "minishell.h"

static char	*append_char(char *result, char c);
static int	process_quote_state(char c, int *in_squote, int *in_dquote);
static void	handle_char_append(char **result, char c, int *i);
static void	handle_variable_expansion(char *word, int *i,
				t_shell *shell, char **result);

char	*expand_word(char *word, t_shell *shell)
{
	char	*result;
	int		i;
	int		in_squote;
	int		in_dquote;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (word[i])
	{
		if (process_quote_state(word[i], &in_squote, &in_dquote))
		{
			i++;
			continue ;
		}
		if (word[i] == '$' && !in_squote && (word[i + 1] == '?'
				|| ft_isalnum_or_underscore(word[i + 1])))
			handle_variable_expansion(word, &i, shell, &result);
		else
			handle_char_append(&result, word[i], &i);
	}
	return (result);
}

static void	handle_variable_expansion(char *word, int *i,
				t_shell *shell, char **result)
{
	char	*var_value;

	var_value = expand_variable(word, i, shell);
	*result = ft_strjoin_free(*result, var_value);
	free(var_value);
}

static void	handle_char_append(char **result, char c, int *i)
{
	*result = append_char(*result, c);
	(*i)++;
}

static char	*append_char(char *result, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	return (ft_strjoin_free(result, temp));
}

static int	process_quote_state(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'')
	{
		if (!*in_dquote)
		{
			*in_squote = !*in_squote;
			return (1);
		}
		return (0);
	}
	if (c == '"')
	{
		if (!*in_squote)
		{
			*in_dquote = !*in_dquote;
			return (1);
		}
		return (0);
	}
	return (0);
}
