/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:32:10 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 10:37:16 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_game(t_game *game)
{
	int	i;

	if (game->mlx)
	{
		i = 0;
		while (i < TOTAL_SPRITES)
		{
			if (game->sprites[i].img)
				mlx_destroy_image(game->mlx, game->sprites[i].img);
			i++;
		}
		i = 0;
		while (i < PLAYER_FRAMES)
		{
			if (game->player_frames[i].img)
				mlx_destroy_image(game->mlx, game->player_frames[i].img);
			i++;
		}
		i = 0;
		while (i < ENEMY_FRAMES)
		{
			if (game->enemy_frames[i].img)
				mlx_destroy_image(game->mlx, game->enemy_frames[i].img);
			i++;
		}
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
	free_enemies(game);
	free_map(game->map);
}
