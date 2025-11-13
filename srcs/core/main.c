#include "minishell.h"

static void	shell_loop(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("minishell: does not accept arguments", 2);
		return (1);
	}
	init_shell(&shell, envp);
	setup_signals();
	shell_loop(&shell);
	cleanup_shell(&shell);
	ft_putendl_fd("exit", 1);
	return (shell.exit_status);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;
	t_ast	*ast;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		shell->token_list = lexer(line);
		free(line);
		if (!shell->token_list)
			continue ;
		ast = parse_tokens(shell->token_list);
		ft_dlstclear(&shell->token_list, free_tokens);
		shell->token_list = NULL;
		handle_heredocs(ast, shell);
		if (ast)
		{
			shell->exit_status = execute_ast(ast, shell);
			ast_free(ast);
		}
	}
}
