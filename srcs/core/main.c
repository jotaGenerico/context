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

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		exit_status;

	if (argc != 1)
		return (1);
	(void)argv;
	init_shell(&shell, envp);
	close_all_fds_except_std();
	shell_loop(&shell);
	exit_status = shell.exit_status;
	cleanup_shell(&shell);
	return (exit_status);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		shell->ast = NULL;
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		shell->token_list = lexer(line);
		free(line);
		if (!shell->token_list)
			continue ;
		shell->ast = parse_tokens(shell->token_list);
		ft_dlstclear(&shell->token_list, free_tokens);
		shell->token_list = NULL;
		handle_heredocs(shell->ast, shell);
		if (shell->ast)
		{
			shell->exit_status = execute_ast(shell->ast, shell);
			ast_free(shell->ast);
			shell->ast = NULL;
		}
	}
}
