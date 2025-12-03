/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:57:35 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 15:57:37 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_with_error(char *arg, t_shell *shell, t_ast *node);
static int	validate_exit_args(char **argv, t_shell *shell, t_ast *node);

int	builtin_exit(t_ast *node, t_shell *shell)
{
	int	code;

	ft_putendl_fd("exit", 1);
	if (validate_exit_args(node->argv, shell, node) != 0)
		return (1);
	code = shell->exit_status;
	if (node->argv[1])
		code = ft_atoi(node->argv[1]) % 256;
	ast_free(node);
	cleanup_shell(shell);
	close_all_fds_except_std();
	exit(code);
}

static void	exit_with_error(char *arg, t_shell *shell, t_ast *node)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	ast_free(node);
	cleanup_shell(shell);
	exit(2);
}

static int	validate_exit_args(char **argv, t_shell *shell, t_ast *node)
{
	if (argv[1] && !ft_isnumeric(argv[1]))
		exit_with_error(argv[1], shell, node);
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}
