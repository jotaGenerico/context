// srcs/executor/exec_heredoc.c
#include "minishell.h"

/* ************************************************************************** */
/* PROCESSA TODOS OS HEREDOCS DA AST (NO PROCESSO PAI)                       */
/* ************************************************************************** */
int	handle_heredocs(t_ast *node, t_shell *shell)
{
	int		pipe_fds[2];
	char	*line;
	int		delimiter_len;

	if (!node)
		return (0);

	// 1. Processa heredoc ATUAL
	if (node->type == NODE_HEREDOC)
	{
		// Cria o pipe
		if (pipe(pipe_fds) == -1)
			return (perror("pipe"), 1);

		// Lê as linhas no PAI (onde readline funciona)
		delimiter_len = ft_strlen(node->filename);
		while (1)
		{
			line = readline("> ");
			if (!line) // EOF (Ctrl+D)
				break ;

			// Checa se é o delimitador
			if (ft_strncmp(line, node->filename, delimiter_len + 1) == 0
				&& (size_t)delimiter_len == ft_strlen(line))
			{
				free(line);
				break ;
			}

			// Escreve no pipe
			ft_putendl_fd(line, pipe_fds[1]);
			free(line);
		}

		// CRÍTICO: Fecha o lado de ESCRITA
		close(pipe_fds[1]);

		// Armazena o FD de LEITURA no nó (será usado depois)
		node->heredoc_fd = pipe_fds[0];
	}

	// 2. Recursão para processar heredocs em toda a árvore
	if (handle_heredocs(node->left, shell) != 0)
		return (1);
	if (handle_heredocs(node->right, shell) != 0)
		return (1);

	return (0);
}
