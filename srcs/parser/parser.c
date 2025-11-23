#include "minishell.h"

t_ast	*ast_new_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = NULL;
	node->argv_quoted = NULL;
	node->filename = NULL;
	node->heredoc_fd = -1;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_list(t_dlist **tokens)
{
	return (parse_and_or(tokens));
}

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
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'", 2);
		return (NULL);
	}
	return (root);
}
