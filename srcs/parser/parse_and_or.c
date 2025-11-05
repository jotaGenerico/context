#include "minishell.h"

t_ast	*parse_and_or(t_dlist **tokens)
{
	t_ast		*left;
	t_ast		*right;
	t_token		*token;
	t_node_type	type;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_AND || token->type == TOKEN_OR)
		{
			if (token->type == TOKEN_AND)
				type = NODE_AND;
			else
				type = NODE_OR;
			*tokens = (*tokens)->next;
			right = parse_pipeline(tokens);
			if (!right)
			{
				ast_free(left);
				return (NULL);
			}
			left = ast_new_node(type, left, right);
			if (!left)
				return (NULL);
		}
		else
			break ;
	}
	return (left);
}
