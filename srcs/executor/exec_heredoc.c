#include "minishell.h"

static int	read_heredoc_input(t_ast *node);

int	handle_heredocs(t_ast *node, t_shell *shell)
{
	(void)shell;
	if (!node)
		return (0);
	if (node->type == NODE_HEREDOC)
	{
		if (read_heredoc_input(node) != 0)
			return (1);
	}
	if (handle_heredocs(node->left, shell) != 0)
		return (1);
	if (handle_heredocs(node->right, shell) != 0)
		return (1);
	return (0);
}

static int	read_heredoc_input(t_ast *node)
{
	int		pipe_fds[2];
	char	*line;
	size_t	delimiter_len;

	if (pipe(pipe_fds) == -1)
		return (perror("pipe"), 1);
	delimiter_len = ft_strlen(node->filename);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, node->filename, delimiter_len + 1) == 0
			&& delimiter_len == ft_strlen(line))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fds[1]);
		free(line);
	}
	close(pipe_fds[1]);
	node->heredoc_fd = pipe_fds[0];
	return (0);
}
