#include "minishell.h"

int	is_builtin(t_ast *node)
{
	if (!node || !node->argv || !node->argv[0])
		return (0);
	return (!ft_strcmp(node->argv[0], "cd")
		|| !ft_strcmp(node->argv[0], "echo")
		|| !ft_strcmp(node->argv[0], "env")
		|| !ft_strcmp(node->argv[0], "exit")
		|| !ft_strcmp(node->argv[0], "export")
		|| !ft_strcmp(node->argv[0], "pwd")
		|| !ft_strcmp(node->argv[0], "unset"));
}
