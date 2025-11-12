#include "minishell.h"

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

const char	*redir_type_to_str(t_node_type type)
{
	if (type == NODE_REDIR_IN)
		return ("<");
	if (type == NODE_REDIR_OUT)
		return (">");
	if (type == NODE_REDIR_APPEND)
		return (">>");
	if (type == NODE_HEREDOC)
		return ("<<");
	return ("?");
}

void	free_redirections(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_REDIR_IN
		|| node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND
		|| node->type == NODE_HEREDOC)
	{
		if (node->filename)
			free(node->filename);
	}
	free_redirections(node->left);
	free_redirections(node->right);
	free(node);
}

int	has_redirections(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_REDIR_IN
		|| node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND
		|| node->type == NODE_HEREDOC)
		return (1);
	return (has_redirections(node->left) || has_redirections(node->right));
}
