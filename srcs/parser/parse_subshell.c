#include "minishell.h"

t_ast	*parse_subshell(t_dlist **tokens)
{
	t_token	*token;
	t_ast	*node;

	if (!*tokens)
		return (NULL);
	token = (*tokens)->content;
	if (token->type == TOKEN_LPAREN)
	{
		*tokens = (*tokens)->next;
		node = parse_and_or(tokens);
		if (!node)
			return (NULL);
		if (!*tokens || ((t_token *)(*tokens)->content)->type != TOKEN_RPAREN)
		{
			ft_putendl_fd("minishell: syntax error: expected ')'", 2);
			ast_free(node);
			return (NULL);
		}
		*tokens = (*tokens)->next;
		return (ast_new_node(NODE_SUBSHELL, node, NULL));
	}
	else
		return (parse_command(tokens));
}
