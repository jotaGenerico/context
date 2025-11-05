#include "minishell.h"

bool	is_operator(char *line, int i)
{
	if (line[i] == '|' || line[i] == '<' || line[i] == '>'
		|| line[i] == '(' || line[i] == ')' || line[i] == '&'
		|| line[i] == ';')
		return (true);
	return (false);
}

static t_token_type	get_operator_type(char *line, int *i)
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
	if (line[*i] == '&')
	{
		if (line[*i + 1] == '&')
		{
			(*i)++;
			return (TOKEN_AND);
		}
		// '&' isolado não é permitido, conforme seu código:
		ft_putendl_fd("minishell: syntax error near unexpected token `&'", 2);
		return (TOKEN_ERROR);
	}

    // >>> INSERÇÃO DA CORREÇÃO PARA O PONTO E VÍRGULA <<<
	if (line[*i] == ';')
	{
		// O ponto e vírgula é um separador de comando de um único caractere
		return (TOKEN_SEMICOLON);
	}
	// >>> FIM DA INSERÇÃO <<<

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
	return (TOKEN_RPAREN);
}

t_token	*create_operator_token(char *line, int *i)
{
	t_token_type	type;
	char			*value;
	int				len;
	int				start;

	start = *i;
	type = get_operator_type(line, i);
	if (type == TOKEN_ERROR)
		return (NULL);
	if (type == TOKEN_OR || type == TOKEN_HEREDOC
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_AND)
		len = 2;
	else
		len = 1;
	value = ft_substr(line, start, len);
	if (!value)
		return (NULL);
	(*i)++;
	return (create_token(type, value));
}
