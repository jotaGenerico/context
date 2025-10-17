/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:46:53 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/13 19:32:54 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	render_tile(t_game *game, int x, int y)
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

int	render_game(t_game *game)
{
	int	x;
	int	y;

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
	render_enemies(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->player_frames[game->current_frame].img,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	render_ui(game);
	return (0);
}

int	game_loop(t_game *game)
{
	static int	anim_counter = 0;
	static int	move_counter = 0;
	int			moved_or_animated;

	if (game->game_over)
		return (0);
	moved_or_animated = 0;
	anim_counter++;
	if (anim_counter >= ANIMATION_SPEED)
	{
		update_animation(game);
		anim_counter = 0;
		moved_or_animated = 1;
	}
	move_counter++;
	if (move_counter >= ENEMY_MOVE_DELAY)
	{
		update_enemies(game);
		move_counter = 0;
		moved_or_animated = 1;
		if (check_enemy_collision(game))
		{
			ft_printf("\n💀 GAME OVER! You were caught by an enemy!\n");
			ft_printf("Moves: %d\n", game->moves);
			game->game_over = 1;
			close_game(game);
		}
	}
	if (moved_or_animated)
		render_game(game);

	return (0);
}

void	render_ui(t_game *game)
{
	char	*moves_str;
	char	*collect_str;
	char	*temp;

	moves_str = ft_itoa(game->moves);
	collect_str = ft_itoa(game->collected);
	temp = ft_strjoin("Moves: ", moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, temp);
	free(temp);
	free(moves_str);
	temp = ft_strjoin("Collected: ", collect_str);
	mlx_string_put(game->mlx, game->win, 10, 40, 0xFFFFFF, temp);
	free(temp);
	free(collect_str);
}
