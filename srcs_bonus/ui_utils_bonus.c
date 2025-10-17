/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:47:51 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 11:17:57 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	render_enemy(t_game *game, t_enemy *enemy)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->enemy_frames[game->enemy_current_frame].img,
		enemy->x * TILE_SIZE, enemy->y * TILE_SIZE);
}

void	render_enemies(t_game *game)
{
	t_enemy	*enemy;

	enemy = game->enemies;
	while (enemy)
	{
		render_enemy(game, enemy);
		enemy = enemy->next;
	}
}
