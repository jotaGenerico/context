/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:19 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:00:21 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_high_fds_except_pipe(void)
{
	int	fd;

	fd = 5;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	close_all_fds_except_std(void)
{
	int	fd;

	fd = 3;
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}
