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
/* HEREDOC HANDLER                                  */
/* ************************************************************************** */

static int	open_heredoc(t_ast *node)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, node->filename) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
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

	// Corrigido para incluir a recursão (ausente no snippet original)
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
		status = open_heredoc(node);

	if (node->right && status == 0)
		status = apply_redirections(node->right, shell);

	return (status);
}
