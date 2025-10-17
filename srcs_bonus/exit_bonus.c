/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:32:36 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 10:37:56 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	close_game(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

int	close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free_enemies(game);
	free_map(game->map);
	exit(0);
	return (0);
}

void	error_exit(char *message)
{
	if (message)
	{
		write(2, "Error\n", 6);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}
