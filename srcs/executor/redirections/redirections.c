#include "minishell.h"

/* ************************************************************************** */
/* REDIRECTIONS HANDLER                              */
/* ************************************************************************** */

static int	open_infile(t_ast *node)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: %s: %s\n",
			node->filename, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_outfile_trunc(t_ast *node)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: %s: %s\n",
			node->filename, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_outfile_append(t_ast *node)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: %s: %s\n",
			node->filename, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/* ************************************************************************** */
/* HEREDOC HANDLER (MODIFICADO)                               */
/* ************************************************************************** */

/*
 * Esta função aplica o FD do heredoc (preenchido por handle_heredocs)
 * ao STDIN. A leitura real do heredoc NÃO acontece aqui.
 */
static int	apply_heredoc(t_ast *node)
{
	// Verifica se o FD é válido (definido em handle_heredocs)
	if (node->heredoc_fd < 0)
	{
		ft_dprintf(2, "minishell: erro interno de heredoc (fd inválido)\n");
		return (-1);
	}

	// Redireciona o STDIN para ler do pipe do heredoc
	if (dup2(node->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(node->heredoc_fd); // Fecha o FD em caso de erro
		return (-1);
	}

	// Fecha o FD original (o duplicado continua aberto em STDIN)
	close(node->heredoc_fd);
	return (0);
}

/* ************************************************************************** */
/* APPLY REDIRECTIONS                                 */
/* ************************************************************************** */

int	apply_redirections(t_ast *node, t_shell *shell)
{
	int	status;

	(void)shell;
	if (!node)
		return (0);

	// Corrigido para incluir a recursão
	if (node->left)
	{
		if (apply_redirections(node->left, shell) != 0)
			return (1);
	}

	status = 0;
	if (node->type == NODE_REDIR_IN)
		status = open_infile(node);
	else if (node->type == NODE_REDIR_OUT)
		status = open_outfile_trunc(node);
	else if (node->type == NODE_REDIR_APPEND)
		status = open_outfile_append(node);
	else if (node->type == NODE_HEREDOC)
		status = apply_heredoc(node); // Modificado

	if (node->right && status == 0)
		status = apply_redirections(node->right, shell);

	return (status);
}
