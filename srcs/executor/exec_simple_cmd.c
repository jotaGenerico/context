#include "minishell.h"

static int	exec_builtin_parent(t_ast *node, t_shell *shell);
static void	child_process(t_ast *node, t_shell *shell);
static t_ast	*get_command_node(t_ast *node);

static t_ast	*get_command_node(t_ast *node)
{
	while (node && node->type != NODE_COMMAND)
		node = node->left;
	return (node);
}

static void	child_process(t_ast *node, t_shell *shell)
{
	char	**envp;
	char	*path;
	t_ast	*cmd_node;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (apply_redirections(node, shell) != 0)
		exit(EXIT_FAILURE);

	cmd_node = get_command_node(node);

	if (is_builtin(cmd_node))
		exec_builtin_child(cmd_node, shell);

	if (!cmd_node || !cmd_node->argv || !cmd_node->argv[0])
		exit(EXIT_FAILURE);

	envp = env_list_to_array(shell->env_list);
	if (!envp)
		exit(EXIT_FAILURE);

	path = find_command_path(cmd_node->argv[0], shell);
	if (!path)
	{
		ft_dprintf(2, "minishell: %s: command not found\n", cmd_node->argv[0]);
		free_char_array(envp);
		exit(127);
	}

	execve(path, cmd_node->argv, envp);

	perror("execve");
	free_char_array(envp);
	free(path);
	exit(126);
}

static int	exec_builtin_parent(t_ast *node, t_shell *shell)
{
	int	sv_in;
	int	sv_out;
	int	sv_err;
	int	status;
	t_ast	*cmd_node;

	if (save_std_fds(&sv_in, &sv_out, &sv_err) == -1)
		return (1);

	if (apply_redirections(node, shell) != 0)
	{
		restore_std_fds(sv_in, sv_out, sv_err);
		return (1);
	}

	cmd_node = get_command_node(node);
	if (!cmd_node)
	{
		restore_std_fds(sv_in, sv_out, sv_err);
		return (1);
	}

	status = exec_builtin(cmd_node, shell);

	restore_std_fds(sv_in, sv_out, sv_err);

	return (status);
}

int	exec_simple_cmd(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;
	t_ast	*cmd_node;

	if (!node)
		return (1);

	cmd_node = get_command_node(node);

	if (!cmd_node || !cmd_node->argv || !cmd_node->argv[0])
		return (0);

	expand_variables(cmd_node->argv, shell);

	if (expand_wildcards(&(cmd_node->argv)) != 0)
	{
		shell->exit_status = 1;
		return (shell->exit_status);
	}

	if (handle_assignment_only(cmd_node, shell))
		return (shell->exit_status);

	if (is_builtin(cmd_node))
	{
		if (!has_redirections(node))
			return (exec_builtin(cmd_node, shell));
		return (exec_builtin_parent(node, shell));
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		child_process(node, shell);

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
	}
	setup_signals();

	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);

	return (shell->exit_status);
}
