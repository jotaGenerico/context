/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:16:24 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 10:16:26 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define TILE_SIZE 64
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

# define SPRITE_WALL 0
# define SPRITE_EMPTY 1
# define SPRITE_COLLECTIBLE 2
# define SPRITE_EXIT 3
# define SPRITE_PLAYER 4
# define TOTAL_SPRITES 5

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		collected;
	int		moves;
	t_img	sprites[5];
}			t_game;

void	read_map(t_game *game, char *map_path);
void	validate_map(t_game *game);
void	check_path(t_game *game);
void	check_retangularity(t_game *game);
void	check_walls(t_game *game);
void	check_components(t_game *game);
void	count_and_locate(t_game *game, int i, int j);
char	**copy_map(char **map, int height);
void	init_game(t_game *game);
int		render_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		close_game(t_game *game);
int		close_window(t_game *game);
void	error_exit(char *msg);
void	free_map(char **map);
void	free_game(t_game *game);

#endif
