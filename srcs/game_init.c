/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:13:49 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/14 10:22:23 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_sprite_or_exit(t_game *game, void **img_ptr, char *path);
static void	load_sprites(t_game *game);

void	init_game(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_map(game->map);
		error_exit("Error: Failed to initialize MLX.");
	}
	win_width = game->map_width * TILE_SIZE;
	win_height = game->map_height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height, "So Long");
	if (!game->win)
	{
		free_game(game);
		error_exit("Error: Failed to create window.");
	}
	load_sprites(game);
	game->moves = 0;
	game->collected = 0;
	render_game(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_loop_hook(game->mlx, render_game, game);
	mlx_loop(game->mlx);
}

static void	load_sprite_or_exit(t_game *game, void **img_ptr, char *path)
{
	int	w;
	int	h;

	*img_ptr = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!(*img_ptr))
	{
		free_game(game);
		error_exit("Error: Failed to load texture: Check XPM path or file.");
	}
}

static void	load_sprites(t_game *game)
{
	load_sprite_or_exit(game, &game->sprites[0].img, "textures/wall.xpm");
	load_sprite_or_exit(game, &game->sprites[1].img, "textures/empty.xpm");
	load_sprite_or_exit(game, &game->sprites[2].img, "textures/"
		"collectible.xpm");
	load_sprite_or_exit(game, &game->sprites[3].img, "textures/exit.xpm");
	load_sprite_or_exit(game, &game->sprites[4].img, "textures/player.xpm");
}
