/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:06 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:08 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_external_cmd(t_ast *cmd_node, t_shell *shell);
static void	child_process(t_ast *node, t_shell *shell);
static void	handle_path_error_child(char *cmd, char **envp, t_shell *shell);

int	execute_forked_cmd(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		child_process(node, shell);
	if (waitpid(pid, &status, 0) == -1)
		perror("waitpid");
	setup_signals();
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (shell->exit_status);
}

static void	execute_external_cmd(t_ast *cmd_node, t_shell *shell)
{
	char	**envp;
	char	*path;

	envp = env_list_to_array(shell->env_list);
	if (!envp)
		clean_exit_child(shell, EXIT_FAILURE);
	path = find_command_path(cmd_node->argv[0], shell);
	if (!path)
		handle_path_error_child(cmd_node->argv[0], envp, shell);
	if (is_directory(path))
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", path);
		free_char_array(envp);
		free(path);
		clean_exit_child(shell, 126);
	}
	close_all_fds_except_std();
	execve(path, cmd_node->argv, envp);
	perror("execve");
	free_char_array(envp);
	free(path);
	clean_exit_child(shell, 126);
}

static void	child_process(t_ast *node, t_shell *shell)
{
	t_ast	*cmd_node;
	int		ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (apply_redirections(node, shell) != 0)
		clean_exit_child(shell, EXIT_FAILURE);
	cmd_node = get_command_node(node);
	if (is_builtin(cmd_node))
	{
		ret = exec_builtin(cmd_node, shell);
		clean_exit_child(shell, ret);
	}
	if (!cmd_node || !cmd_node->argv || !cmd_node->argv[0])
		clean_exit_child(shell, EXIT_FAILURE);
	execute_external_cmd(cmd_node, shell);
}

static void	handle_path_error_child(char *cmd, char **envp, t_shell *shell)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			ft_dprintf(2, "minishell: %s: No such file or directory\n", cmd);
		else if (access(cmd, X_OK) != 0)
			ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
		else if (is_directory(cmd))
			ft_dprintf(2, "minishell: %s: Is a directory\n", cmd);
		else
			ft_dprintf(2, "minishell: %s: command not found\n", cmd);
	}
	else
		ft_dprintf(2, "minishell: %s: command not found\n", cmd);
	free_char_array(envp);
	clean_exit_child(shell, 127);
}
