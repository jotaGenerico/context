#include "minishell.h"

static void	shell_loop(t_shell *shell)
{
	char	*line;
	t_ast	*ast;

	while (1)
	{
		// 1. READ: Lê a linha de comando do usuário
		line = readline("minishell$ ");
		if (!line) // EOF (Ctrl+D)
			break ;

		// 2. Adiciona ao histórico do readline (se não for vazia)
		if (*line)
			add_history(line);

		// 3. LEXER: Converte a linha em tokens
		shell->token_list = lexer(line);
		free(line);
		if (!shell->token_list)
			continue ;

		// 4. EXPANDER: Expande variáveis de ambiente e remove aspas
		expand_tokens(shell->token_list, shell);

		// 5. PARSER: Constrói a Árvore de Sintaxe Abstrata (AST)
		ast = parse_tokens(shell->token_list);

		// ✅ CORREÇÃO LEAK 1: Libera tokens após o parse
		ft_dlstclear(&shell->token_list, free_tokens);
		shell->token_list = NULL;

		// 5.5. HEREDOCS: Processa todos os heredocs antes da execução
		// (Esta é a correção principal de arquitetura)
		handle_heredocs(ast, shell);

		// 6. EXECUTE: Executa a AST
		if (ast)
		{
			shell->exit_status = execute_ast(ast, shell);
			ast_free(ast);
		}
	}
}

/*
 * Ponto de entrada do programa.
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("minishell: does not accept arguments", 2);
		return (1);
	}

	// Configura o ambiente, o status de saída e a lista de tokens/env.
	init_shell(&shell, envp);

	// Configura a manipulação de sinais (Ctrl+C, Ctrl+\)
	setup_signals();

	// Inicia o loop principal
	shell_loop(&shell);

	// Limpeza antes de sair (libera env_list, tokens, etc.)
	cleanup_shell(&shell);
	ft_putendl_fd("exit", 1);
	return (shell.exit_status);
}
