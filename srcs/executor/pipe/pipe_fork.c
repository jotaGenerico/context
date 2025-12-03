/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:58:29 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 15:58:31 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_one_child(t_ast *cmd, int i, t_fork_data *data);
static void	exec_child_command(t_ast *cmd, t_shell *shell);
static void	setup_and_exec(t_ast *cmd, int i, t_fork_data *data);

int	fork_all_children(t_ast **cmds, pid_t *pids, t_fork_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		pids[i] = fork_one_child(cmds[i], i, data);
		if (pids[i] < 0)
			return (i);
		i++;
	}
	return (i);
}

int	fork_and_wait(t_ast **cmds, t_fork_data *data, pid_t *pids)
{
	int	children;

	children = fork_all_children(cmds, pids, data);
	return (wait_for_children(pids, children, data->shell));
}

static void	exec_child_command(t_ast *cmd, t_shell *shell)
{
	char	*path;
	int		has_slash;

	child_signals();
	if (apply_redirections(cmd, shell) != 0)
		exit(1);
	if (is_builtin(cmd))
		exit(exec_builtin_child(cmd, shell));
	path = find_command_path(cmd->argv[0], shell);
	if (!path)
	{
		has_slash = (ft_strchr(cmd->argv[0], '/') != NULL);
		handle_command_not_found(cmd->argv[0], has_slash);
	}
	exec_external_command(cmd, path, shell);
}

static void	setup_and_exec(t_ast *cmd, int i, t_fork_data *data)
{
	if (setup_child_pipes(i, data->n, data->pipes) != 0)
		exit(1);
	close_all_pipes(data->pipes, data->n - 1);
	exec_child_command(cmd, data->shell);
}

static int	fork_one_child(t_ast *cmd, int i, t_fork_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
		setup_and_exec(cmd, i, data);
	return (pid);
}
