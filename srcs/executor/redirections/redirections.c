#include "minishell.h"

static int	open_infile(t_ast *node);
static int	open_outfile_trunc(t_ast *node);
static int	open_outfile_append(t_ast *node);
static int	apply_heredoc(t_ast *node);

int	apply_redirections(t_ast *node, t_shell *shell)
{
	int	status;

	(void)shell;
	if (!node)
		return (0);
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
		status = apply_heredoc(node);
	if (node->right && status == 0)
		status = apply_redirections(node->right, shell);
	return (status);
}

static int	apply_heredoc(t_ast *node)
{
	if (node->heredoc_fd < 0)
	{
		ft_dprintf(2, "minishell: internal heredoc error (invalid fd)\n");
		return (-1);
	}
	if (dup2(node->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(node->heredoc_fd);
		return (-1);
	}
	close(node->heredoc_fd);
	return (0);
}

static int	open_outfile_append(t_ast *node)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(node->filename);
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

static int	open_outfile_trunc(t_ast *node)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(node->filename);
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

static int	open_infile(t_ast *node)
{
	int		fd;
	char	*clean_filename;

	clean_filename = process_filename(node->filename);
	if (!clean_filename)
		return (-1);
	fd = open(clean_filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(clean_filename);
		free(clean_filename);
		return (-1);
	}
	free(clean_filename);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
