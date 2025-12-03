/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:58:35 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 15:58:38 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	setup_child_pipes(int i, int n, int *pipes)
{
	if (i > 0)
	{
		if (dup2(pipes[2 * (i - 1)], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	if (i < n - 1)
	{
		if (dup2(pipes[2 * i + 1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	return (0);
}

int	check_command_access(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", cmd);
		return (127);
	}
	if (is_directory(cmd))
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", cmd);
		return (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
		return (126);
	}
	return (0);
}

void	handle_command_not_found(char *cmd, int has_slash)
{
	int	exit_code;

	if (has_slash)
	{
		exit_code = check_command_access(cmd);
		if (exit_code != 0)
			exit(exit_code);
		ft_dprintf(2, "minishell: %s: command not found\n", cmd);
		exit(127);
	}
	ft_dprintf(2, "minishell: %s: command not found\n", cmd);
	exit(127);
}

void	exec_external_command(t_ast *cmd, char *path, t_shell *shell)
{
	char	**env_array;

	env_array = env_list_to_array(shell->env_list);
	execve(path, cmd->argv, env_array);
	perror("execve");
	free_char_array(env_array);
	free(path);
	exit(126);
}
