#include "minishell.h"

static void	execute_external_cmd(t_ast *cmd_node, t_shell *shell);
static void	child_process(t_ast *node, t_shell *shell);

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

static void	child_process(t_ast *node, t_shell *shell)
{
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
	execute_external_cmd(cmd_node, shell);
}
