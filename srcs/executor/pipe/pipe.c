/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:58:44 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/01 15:58:46 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pipeline(t_ast **cmds, int n, t_shell *shell)
{
	t_fork_data	data;
	pid_t		*pids;
	int			ret;

	if (n <= 0)
		return (1);
	if (n == 1)
		return (execute_ast(cmds[0], shell));
	data.pipes = alloc_pipes(n - 1);
	if (!data.pipes)
		return (perror("minishell: pipe"), 1);
	pids = alloc_pids(n);
	if (!pids)
		return (free_pipes(data.pipes, n - 1), perror("minishell: fork"), 1);
	data.n = n;
	data.shell = shell;
	ret = fork_and_wait(cmds, &data, pids);
	free_pipes(data.pipes, n - 1);
	free(pids);
	return (ret);
}
