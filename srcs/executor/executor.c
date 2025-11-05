#include "minishell.h"

int	execute_ast(t_ast *node, t_shell *shell)
{
	if (!node)
		return (1);
	/*
	 * O nó raiz do comando pode ser NODE_COMMAND ou um NODE_REDIR_*
	 * Redirecionamentos são a raiz da AST quando aparecem primeiro,
	 * mas o executor trata todos como um 'simple_cmd' único que
	 * contém sua própria lógica de redireção/execução.
	 */
	if (node->type == NODE_COMMAND
		|| node->type == NODE_REDIR_IN
		|| node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND
		|| node->type == NODE_HEREDOC)
		return (exec_simple_cmd(node, shell));
	if (node->type == NODE_PIPE)
		return (exec_pipeline(node, shell));
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (exec_and_or(node, shell));
	if (node->type == NODE_SUBSHELL)
		return (exec_subshell(node, shell));
	if (node->type == NODE_SEQUENCE)
	{
		execute_ast(node->left, shell);
		return (execute_ast(node->right, shell));
    }
	return (1);
}
