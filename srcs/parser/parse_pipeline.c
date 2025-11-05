#include "minishell.h"

t_ast	*parse_pipeline(t_dlist **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_token	*token;

	left = parse_subshell(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_PIPE)
		{
			*tokens = (*tokens)->next;
			right = parse_subshell(tokens);
			if (!right)
			{
				ast_free(left);
				return (NULL);
			}
			left = ast_new_node(NODE_PIPE, left, right);
			if (!left)
				return (NULL);
		}
		else
			break ;
	}
	return (left);
}
