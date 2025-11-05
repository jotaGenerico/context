#include "minishell.h"

/* ************************************************************************** */
/*                         REDIRECTIONS UTILS                                 */
/* ************************************************************************** */

/* Fecha o FD com verificação de erro (ignora FDs inválidos) */
void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

/* Retorna string descritiva para debugging ou logs */
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

/* Limpa toda a subárvore de redireções (útil em erros de parsing) */
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

// bool	has_redirections(t_ast *node)
// {
// 	if (!node)
// 		return (false);
// 	// Busca na sub-árvore de redirecionamento (à esquerda)
// 	if (has_redirections(node->left))
// 		return (true);
// 	// Verifica se o nó atual é um redirecionamento
// 	return (node->type >= NODE_REDIR_IN && node->type <= NODE_HEREDOC);
// }

bool	has_redirections(t_ast *node)
{
	if (!node)
		return (false);

	// 1. Verifica se o nó atual é uma redireção (retorno imediato)
	if (node->type == NODE_REDIR_IN
		|| node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND
		|| node->type == NODE_HEREDOC)
		return (true);

	// 2. Busca recursiva em AMBOS os filhos (left E right)
	return (has_redirections(node->left) || has_redirections(node->right));
}
