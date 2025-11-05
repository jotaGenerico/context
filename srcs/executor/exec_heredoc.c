// srcs/executor/exec_heredoc.c
#include "minishell.h"

/* ************************************************************************** */
/* CHILD PROCESS – lê linhas até o delimitador                 */
/* ************************************************************************** */
static void	heredoc_reader(t_ast *node, int pipe_w_fd, t_shell *shell)
{
	char	*line;
	int		delimiter_len;

    // >>> CORREÇÃO CRÍTICA DO SINAL NO FILHO (PARA SAIR DO READLINE COM Ctrl+C) <<<
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

	delimiter_len = ft_strlen(node->filename);
	while (1)
	{
		line = readline("> ");
		if (!line) // Chegou no EOF (Ctrl+D) ou interrupção (Ctrl+C no DFL)
			break ;
		/* Se encontrar o delimitador, encerra o loop */
		if (ft_strncmp(line, node->filename, delimiter_len + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_w_fd);
		free(line);
	}
	close(pipe_w_fd);
	cleanup_shell(shell);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/* COORDENA TODOS OS HEREDOCS DA AST                           */
/* ************************************************************************** */
int	handle_heredocs(t_ast *node, t_shell *shell)
{
	int		pipe_fds[2];
	char	*line;
	int		delimiter_len;
	int		ret;

	if (!node)
		return (0);
	ret = 0;
	if (node->type == NODE_HEREDOC)
	{
		// 1. Cria o pipe
		if (pipe(pipe_fds) == -1)
			return (perror("pipe"), 1);

		/* >>> CORREÇÃO CRÍTICA DO FLUXO: LER NO PROCESSO PAI <<< */
		// O processo PAI (minishell) está ativo, então readline() funciona.
		delimiter_len = ft_strlen(node->filename);
		while (1)
		{
			// O prompt '>' é padrão do bash, readline lida com ele.
			line = readline("> ");
			if (!line) // EOF (Ctrl+D)
				break ;

			/* Se encontrar o delimitador, encerra o loop */
			if (ft_strncmp(line, node->filename, delimiter_len + 1) == 0 && (size_t)delimiter_len == ft_strlen(line))
			{
				free(line);
				break ;
			}
			// Escreve no lado de escrita (pipe_fds[1])
			ft_putendl_fd(line, pipe_fds[1]);
			free(line);
		}

		// 2. Fechar o lado de escrita do pipe (AGORA NO PAI)
		close(pipe_fds[1]);

		// 3. Armazenar o lado de leitura para o próximo comando (dup2 será usado mais tarde)
		node->heredoc_fd = pipe_fds[0];
	}

	// Navegação recursiva (mantida)
	ret |= handle_heredocs(node->left, shell);
	ret |= handle_heredocs(node->right, shell);

	return (ret);
}
