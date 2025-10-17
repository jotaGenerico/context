/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:02:12 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 10:02:15 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	update_animation(t_game *game)
{
	game->frame_counter++;
	if (game->frame_counter >= ANIMATION_SPEED)
	{
		game->current_frame = (game->current_frame + 1) % PLAYER_FRAMES;
		game->enemy_current_frame = (game->enemy_current_frame + 1) % ENEMY_FRAMES;
		game->frame_counter = 0;
	}
}
