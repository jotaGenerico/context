/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:14:36 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/17 09:57:00 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>

# define TILE_SIZE 100
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define SPRITE_WALL 0
# define SPRITE_EMPTY 1
# define SPRITE_COLLECTIBLE 2
# define SPRITE_EXIT 3
# define SPRITE_PLAYER 4
# define SPRITE_ENEMY 5
# define TOTAL_SPRITES 6

# define ANIMATION_SPEED 150
# define ENEMY_CHAR 'X'
# define ENEMY_SPEED 150
# define ENEMY_MOVE_DELAY 150
# define PLAYER_FRAMES 4
# define ENEMY_FRAMES 4

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_enemy
{
	int				x;
	int				y;
	int				direction;
	struct s_enemy	*next;
}	t_enemy;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	int			collectibles;
	int			collected;
	int			moves;
	t_img		sprites[TOTAL_SPRITES];
	t_img		player_frames[PLAYER_FRAMES];
	int			current_frame;
	int			frame_counter;
	t_img		enemy_frames[ENEMY_FRAMES];
	int			enemy_current_frame;
	t_enemy		*enemies;
	int			enemy_count;
	int			game_over;
}	t_game;

void		read_map(t_game *game, char *map_path);
void		validate_map(t_game *game);
void		check_path(t_game *game);
void		check_retangularity(t_game *game);
void		check_walls(t_game *game);
void		check_components(t_game *game);
void		count_and_locate(t_game *game, int i, int j);
char		**copy_map(char **map, int height);
void		free_map(char **map);
void		init_game(t_game *game);
void		init_enemies(t_game *game);
int			game_loop(t_game *game);
int			render_game(t_game *game);
int			handle_keypress(int keycode, t_game *game);
void		move_enemy(t_game *game, t_enemy *enemy);
void		add_enemy(t_game *game, int x, int y);
void		update_enemies(t_game *game);
void		free_enemies(t_game *game);
int			check_enemy_collision(t_game *game);
void		update_animation(t_game *game);
void		render_ui(t_game *game);
void		free_game(t_game *game);
int			close_game(t_game *game);
int			close_window(t_game *game);
void		error_exit(char *msg);
void		load_sprites(t_game *game);
void		load_player_animations(t_game *game);
int			render_game(t_game *game);
int			game_loop(t_game *game);
void		render_ui(t_game *game);
void		render_enemy(t_game *game, t_enemy *enemy);
void		render_enemies(t_game *game);
void		render_tile(t_game *game, int x, int y);
void		load_enemy_animations(t_game *game);

#endif
