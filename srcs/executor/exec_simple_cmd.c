#include "minishell.h"

static int		exec_builtin_parent(t_ast *node, t_shell *shell);

int	exec_simple_cmd(t_ast *node, t_shell *shell)
{
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
			shell->exit_status = exec_builtin(cmd_node, shell);
		else
			shell->exit_status = exec_builtin_parent(node, shell);
		return (shell->exit_status);
	}
	return (execute_forked_cmd(node, shell));
}

static int	exec_builtin_parent(t_ast *node, t_shell *shell)
{
	int		sv_in;
	int		sv_out;
	int		sv_err;
	int		status;
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
