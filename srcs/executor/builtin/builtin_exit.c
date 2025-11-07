#include "minishell.h"

/*
 * builtin_exit: termina o shell com código apropriado
 * - Se nenhum argumento → usa shell->exit_status
 * - Se argumento numérico → usa atoi(argv[1]) % 256
 * - Caso erro de argumento → imprime erro e retorna 1
 */
int	builtin_exit(char **argv, t_shell *shell)
{
	int	code;

	ft_putendl_fd("exit", 1);
	if (argv[1])
	{
		if (!ft_isnumeric(argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);

			// Ações de limpeza antes de sair com erro
			cleanup_shell(shell);
			free_char_array(argv);
			exit(255);
		}
		if (argv[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			// Não sai do shell, apenas retorna o erro, NÃO PRECISA DE CLEANUP
			return (1);
		}
	}
	// Ação de limpeza para saída válida (exit ou exit N)

    // Se chegou até aqui, a saída é válida
	code = shell->exit_status;
	if (argv[1])
		code = ft_atoi(argv[1]) % 256;

	cleanup_shell(shell);
	free_char_array(argv);
	exit(code);
}
