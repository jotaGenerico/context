#include "minishell.h"

/* ************************************************************************** */
/*                           PIPE UTILS                                       */
/* ************************************************************************** */

/*
 * Aloca um array linear de pipes: int *pipes = malloc(sizeof(int) * 2 * n_pipes)
 * Cada pipe i terá:
 *  read  = pipes[2*i + 0]
 *  write = pipes[2*i + 1]
 */
int	*alloc_pipes(int n_pipes)
{
	int	*pipes;
	int	i;

	if (n_pipes <= 0)
		return (NULL);
	pipes = malloc(sizeof(int) * 2 * n_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n_pipes)
	{
		if (pipe(&pipes[2 * i]) == -1)
		{
			perror("pipe");
			while (--i >= 0)
			{
				close(pipes[2 * i]);
				close(pipes[2 * i + 1]);
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

/* Fecha e libera todos os pipes */
void	free_pipes(int *pipes, int n_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < n_pipes)
	{
		close(pipes[2 * i]);
		close(pipes[2 * i + 1]);
		i++;
	}
	free(pipes);
}

/* Fecha todos os pipes sem liberar memória (para uso nos filhos) */
void	close_all_pipes(int *pipes, int n_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < n_pipes)
	{
		close(pipes[2 * i]);
		close(pipes[2 * i + 1]);
		i++;
	}
}

/* Aloca vetor de pids */
pid_t	*alloc_pids(int n)
{
	if (n <= 0)
		return (NULL);
	return (malloc(sizeof(pid_t) * n));
}

/*
 * Espera todos os processos da pipeline e retorna o status do último.
 */
int	wait_for_children(pid_t *pids, int n, t_shell *shell)
{
	int	i;
	int	status;
	int	last_status;

	if (!pids || n <= 0)
		return (1);
	last_status = 0;
	i = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &status, 0) != -1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			shell->exit_status = last_status;
		}
		i++;
	}
	return (last_status);
}
