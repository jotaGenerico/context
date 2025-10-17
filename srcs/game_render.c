/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:13:43 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/13 20:21:25 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_tile(t_game *game, int x, int y);

int	render_game(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->sprites[SPRITE_PLAYER].img,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	return (0);
}

static void	render_tile(t_game *game, int x, int y)
{
	void	*sprite;

	sprite = NULL;
	if (game->map[y][x] == '1')
		sprite = game->sprites[SPRITE_WALL].img;
	else if (game->map[y][x] == 'C')
		sprite = game->sprites[SPRITE_COLLECTIBLE].img;
	else if (game->map[y][x] == 'E')
		sprite = game->sprites[SPRITE_EXIT].img;
	else
		sprite = game->sprites[SPRITE_EMPTY].img;
	if (sprite)
		mlx_put_image_to_window(game->mlx, game->win, sprite,
			x * TILE_SIZE, y * TILE_SIZE);
}
