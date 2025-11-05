#include "minishell.h"

static void	print_indent(int depth)
{
	while (depth-- > 0)
		ft_putstr_fd("  ", 1);
}

t_ast	*ast_new_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = NULL;
	node->filename = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

void	ast_free(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
			free(node->argv[i++]);
		free(node->argv);
	}
	free(node->filename);
	ast_free(node->left);
	ast_free(node->right);
	free(node);
}

void	print_ast(t_ast *node, int depth)
{
	int	i;

	if (!node)
		return ;
	print_indent(depth);
	ft_printf("(%d)", node->type);
	if (node->argv && node->argv[0])
	{
		ft_putstr_fd(" CMD: ", 1);
		i = 0;
		while (node->argv[i])
		{
			ft_putstr_fd(node->argv[i], 1);
			if (node->argv[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (node->filename)
	{
		ft_putstr_fd(" FILE: ", 1);
		ft_putstr_fd(node->filename, 1);
	}
	ft_putendl_fd("", 1);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
