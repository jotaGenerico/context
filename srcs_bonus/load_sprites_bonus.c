/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:12:48 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 10:27:52 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	load_sprite_or_exit(t_game *game, void **img_ptr, char *path);

void	load_sprites(t_game *game)
{
	load_sprite_or_exit(game, &game->sprites[SPRITE_WALL].img,
		"textures/wall.xpm");
	load_sprite_or_exit(game, &game->sprites[SPRITE_EMPTY].img,
		"textures/empty.xpm");
	load_sprite_or_exit(game, &game->sprites[SPRITE_COLLECTIBLE].img,
		"textures/collectible.xpm");
	load_sprite_or_exit(game, &game->sprites[SPRITE_EXIT].img,
		"textures/exit.xpm");
	load_sprite_or_exit(game, &game->sprites[SPRITE_PLAYER].img,
		"textures/player.xpm");
	load_sprite_or_exit(game, &game->sprites[SPRITE_ENEMY].img,
		"textures/enemy.xpm");
}

void	load_enemy_animations(t_game *game)
{
	load_sprite_or_exit(game, &game->enemy_frames[0].img,
		"textures/enemy1.xpm");
	load_sprite_or_exit(game, &game->enemy_frames[1].img,
		"textures/enemy2.xpm");
	load_sprite_or_exit(game, &game->enemy_frames[2].img,
		"textures/enemy3.xpm");
	load_sprite_or_exit(game, &game->enemy_frames[3].img,
		"textures/enemy4.xpm");
}

void	load_player_animations(t_game *game)
{
	load_sprite_or_exit(game, &game->player_frames[0].img,
		"textures/player1.xpm");
	load_sprite_or_exit(game, &game->player_frames[1].img,
		"textures/player2.xpm");
	load_sprite_or_exit(game, &game->player_frames[2].img,
		"textures/player3.xpm");
	load_sprite_or_exit(game, &game->player_frames[3].img,
		"textures/player4.xpm");
}

static void	load_sprite_or_exit(t_game *game, void **img_ptr, char *path)
{
	int	w;
	int	h;

	*img_ptr = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!(*img_ptr))
	{
		free_game(game);
		error_exit("Failed to load texture (check XPM path)");
	}
}
