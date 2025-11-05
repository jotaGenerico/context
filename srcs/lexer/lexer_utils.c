#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	free_tokens(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	print_tokens(t_dlist *tokens)
{
	const char	*types[] = {"ERROR", "WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
		"REDIR_APPEND", "HEREDOC", "AND", "OR", "LPAREN", "RPAREN"};

	while (tokens)
	{
		t_token	*token = (t_token *)tokens->content;
		ft_printf("[%s: '%s'] ", types[token->type], token->value);
		tokens = tokens->next;
	}
	ft_printf("\n");
}
