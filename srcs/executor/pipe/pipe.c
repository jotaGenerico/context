#include "minishell.h"

extern char **environ;

static void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	child_exec(t_ast *cmd, int i, int n, int *pipes, t_shell *shell)
{
	char	*path;
	char	**env_array;

	if (i > 0 && dup2(pipes[2 * (i - 1)], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}

	if (i < n - 1 && dup2(pipes[2 * i + 1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}

	close_all_pipes(pipes, n - 1);
	child_signals();

	if (apply_redirections(cmd, shell) != 0)
		exit(1);

	if (is_builtin(cmd))
		exit(exec_builtin_child(cmd, shell));

	path = find_command_path(cmd->argv[0], shell);
	if (!path)
	{
		if (ft_strchr(cmd->argv[0], '/'))
		{
			if (access(cmd->argv[0], F_OK) == 0)
			{
				if (is_directory(cmd->argv[0]))
				{
					ft_dprintf(2, "minishell: %s: Is a directory\n",
						cmd->argv[0]);
					exit(126);
				}
				if (access(cmd->argv[0], X_OK) != 0)
				{
					ft_dprintf(2, "minishell: %s: Permission denied\n",
						cmd->argv[0]);
					exit(126);
				}
				ft_dprintf(2, "minishell: %s: command not found\n",
					cmd->argv[0]);
				exit(127);
			}
			ft_dprintf(2, "minishell: %s: No such file or directory\n",
				cmd->argv[0]);
			exit(127);
		}
		ft_dprintf(2, "minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}

	env_array = env_list_to_array(shell->env_list);
	execve(path, cmd->argv, env_array);

	perror("execve");
	free_char_array(env_array);
	free(path);
	exit(126);
}

int	run_pipeline(t_ast **cmds, int n, t_shell *shell)
{
	int		*pipes;
	pid_t	*pids;
	int		i;
	int		ret;

	if (n <= 0)
		return (1);
	if (n == 1)
		return (execute_ast(cmds[0], shell));

	pipes = alloc_pipes(n - 1);
	if (!pipes)
	{
		perror("minishell: pipe");
		return (1);
	}
	pids = alloc_pids(n);
	if (!pids)
	{
		free_pipes(pipes, n - 1);
		perror("minishell: fork");
		return (1);
	}

	i = 0;
	while (i < n)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("minishell: fork");
			break ;
		}
		if (pids[i] == 0)
			child_exec(cmds[i], i, n, pipes, shell);
		i++;
	}

	free_pipes(pipes, n - 1);
	ret = wait_for_children(pids, i, shell);
	free(pids);
	return (ret);
}
