/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:02:36 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 12:59:57 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static void	init_mlx(t_game *game);
static void	setup_game_state(t_game *game);
static void	setup_hooks(t_game *game);

void	init_game(t_game *game)
{
	init_mlx(game);
	load_sprites(game);
	load_player_animations(game);
	load_enemy_animations(game);
	init_enemies(game);
	setup_game_state(game);
	render_game(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
}

static void	init_mlx(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_map(game->map);
		error_exit("MLX initialization failed");
	}
	win_width = game->map_width * TILE_SIZE;
	win_height = game->map_height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height,
			"So Long - Bonus");
	if (!game->win)
	{
		free_game(game);
		error_exit("Window creation failed");
	}
}

static void	setup_game_state(t_game *game)
{
	game->moves = 0;
	game->collected = 0;
	game->current_frame = 0;
	game->frame_counter = 0;
	game->game_over = 0;
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
