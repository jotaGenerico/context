#include "minishell.h"

int	exec_and_or(t_ast *node, t_shell *shell)
{
	int	left_status;

	left_status = execute_ast(node->left, shell);
	if (node->type == NODE_AND && left_status == 0)
		return (execute_ast(node->right, shell));
	else if (node->type == NODE_OR && left_status != 0)
		return (execute_ast(node->right, shell));
	return (left_status);
}
