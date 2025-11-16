#include "minishell.h"

static void	exit_with_error(char *arg, t_shell *shell, char **argv);
static int	validate_exit_args(char **argv, t_shell *shell);

int	builtin_exit(t_ast *node, t_shell *shell)
{
	int	code;

	ft_putendl_fd("exit", 1);
	if (validate_exit_args(node->argv, shell) != 0)
		return (1);
	code = shell->exit_status;
	if (node->argv[1])
		code = ft_atoi(node->argv[1]) % 256;
	ast_free(node);
	cleanup_shell(shell);
	exit(code);
}

static void	exit_with_error(char *arg, t_shell *shell, char **argv)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	cleanup_shell(shell);
	free_char_array(argv);
	exit(255);
}

static int	validate_exit_args(char **argv, t_shell *shell)
{
	if (argv[1] && !ft_isnumeric(argv[1]))
		exit_with_error(argv[1], shell, argv);
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}
