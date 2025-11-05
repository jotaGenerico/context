#include "minishell.h"

t_ast	*parse_tokens(t_dlist *tokens)
{
	t_ast	*root;
	t_dlist	*current;

	current = tokens;
	if (!current)
		return (NULL);
	root = parse_list(&current);
	if (!root)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		return (NULL);
	}
	if (current)
	{
		ft_putendl_fd("minishell: syntax error: extra tokens at end", 2);
		ast_free(root);
		return (NULL);
	}
	return (root);
}

t_ast	*parse_list(t_dlist **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_token	*token;

	left = parse_and_or(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_SEMICOLON)
		{
			*tokens = (*tokens)->next;
			right = parse_and_or(tokens);
			if (!right)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
				ast_free(left);
				return (NULL);
			}
			left = ast_new_node(NODE_SEQUENCE, left, right);
			if (!left)
				return (NULL);
		}
		else
			break ;
	}
	return (left);
}
