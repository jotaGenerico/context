#include "minishell.h"

static void	free_ast_content(t_ast *node);

void	ast_free(t_ast *node)
{
	if (!node)
		return ;
	ast_free(node->left);
	ast_free(node->right);
	free_ast_content(node);
	free(node);
}

static void	free_ast_content(t_ast *node)
{
	if (!node)
		return ;
	if (node->argv)
		free_char_array(node->argv);
	if (node->filename)
		free(node->filename);
	if (node->type == NODE_HEREDOC && node->heredoc_fd != -1)
		safe_close(node->heredoc_fd);
}
