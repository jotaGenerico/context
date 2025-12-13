/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:02:27 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 13:02:32 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_loop(t_shell *shell);
static int	process_input(t_shell *shell, char *line);
static int	handle_heredoc_result(t_shell *shell, int heredoc_result);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		exit_status;

	if (argc != 1)
		return (1);
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	close_all_fds_except_std();
	shell_loop(&shell);
	exit_status = shell.exit_status;
	cleanup_shell(&shell);
	return (exit_status);
}

static int	handle_heredoc_result(t_shell *shell, int heredoc_result)
{
	if (heredoc_result == 130 || heredoc_result != 0)
	{
		ast_free(shell->ast);
		shell->ast = NULL;
		return (1);
	}
	return (0);
}

static int	process_input(t_shell *shell, char *line)
{
	int	heredoc_result;

	shell->token_list = lexer(line);
	if (!shell->token_list)
		return (1);
	shell->ast = parse_tokens(shell->token_list);
	ft_dlstclear(&shell->token_list, free_tokens);
	shell->token_list = NULL;
	if (!shell->ast)
		return (1);
	heredoc_result = handle_heredocs(shell->ast, shell);
	if (handle_heredoc_result(shell, heredoc_result))
		return (1);
	shell->exit_status = execute_ast(shell->ast, shell);
	ast_free(shell->ast);
	shell->ast = NULL;
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		shell->ast = NULL;
		line = readline("minishell$ ");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			shell->exit_status = 130;
		}
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		process_input(shell, line);
		free(line);
	}
}
