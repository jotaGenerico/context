#include "minishell.h"

int	exec_builtin(t_ast *node, t_shell *shell)
{
	if (ft_strcmp(node->argv[0], "cd") == 0)
		return (builtin_cd(node->argv, shell));
	else if (ft_strcmp(node->argv[0], "echo") == 0)
		return (builtin_echo(node->argv));
	else if (ft_strcmp(node->argv[0], "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(node->argv[0], "exit") == 0)
		return (builtin_exit(node->argv, shell));
	else if (ft_strcmp(node->argv[0], "export") == 0)
		return (builtin_export(node->argv, shell));
	else if (ft_strcmp(node->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(node->argv[0], "unset") == 0)
		return (builtin_unset(node->argv, shell));
	return (1);
}

int	exec_builtin_child(t_ast *node, t_shell *shell)
{
	int	code;

	code = exec_builtin(node, shell);
	exit(code);
}
