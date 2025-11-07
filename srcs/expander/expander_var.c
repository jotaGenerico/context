#include "minishell.h"

static char	*get_exit_status(t_shell *shell)
{
	return (ft_itoa(shell->exit_status));
}

// Sua função auxiliar para expandir variáveis
static char	*expand_variable(char *word, int *i, t_shell *shell)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*expanded;

	(*i)++;
	if (word[*i] == '?')
	{
		(*i)++;
		return (get_exit_status(shell));
	}
	// get_var_name_len está em expander_utils.c
	var_len = get_var_name_len(&word[*i]);
	if (var_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(word, *i, var_len);
	if (!var_name)
		return (NULL);
	*i += var_len;
	var_value = get_env_value(var_name, shell);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	expanded = ft_strdup(var_value);
	return (expanded);
}

static char	*append_char(char *result, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	// ft_strjoin_free é assumida para gerenciar a memória
	return (ft_strjoin_free(result, temp));
}

char	*expand_word(char *word, t_shell *shell)
{
	char	*result;
	char	*var_value;
	int		i;
	bool	in_squote; // Estado: Dentro de aspas simples (bloqueia tudo)
	bool	in_dquote; // Estado: Dentro de aspas duplas (permite $)

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_squote = false;
	in_dquote = false;
	while (word[i])
	{
		// 1. Gerenciamento de Aspas Simples (Citação Forte)
		if (word[i] == '\'')
		{
			if (!in_dquote) // Aspas simples só alternam se não estivermos em aspas duplas
				in_squote = !in_squote;
			i++;
			continue ; // Remove a aspa do resultado
		}

		// 2. Gerenciamento de Aspas Duplas (Citação Fraca)
		if (word[i] == '"')
		{
			if (!in_squote) // Aspas duplas só alternam se não estivermos em aspas simples
				in_dquote = !in_dquote;
			i++;
			continue ; // Remove a aspa do resultado
		}

		// 3. Expansão Condicional: SÓ expande se não estiver em aspas simples ('!in_squote')
		if (word[i] == '$' && !in_squote && (word[i + 1] == '?'
				|| ft_isalnum_or_underscore(word[i + 1])))
		{
			var_value = expand_variable(word, &i, shell);
			result = ft_strjoin_free(result, var_value);
			free(var_value);
		}
		else
		{
			result = append_char(result, word[i]);
			i++;
		}
	}
	return (result);
}

void	expand_variables(char **argv, t_shell *shell)
{
	int		i;
	char	*expanded_word;

	i = 0;
	while (argv[i])
	{
		// Chama a função expand_word (que existe neste arquivo)
		expanded_word = expand_word(argv[i], shell);

		// TODO: Adicione tratamento de erro de alocação aqui
		if (!expanded_word)
			return;

		free(argv[i]); // Libera a string antiga
		argv[i] = expanded_word; // Substitui pela nova string expandida
		i++;
	}
}
