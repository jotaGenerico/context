#include "so_long_bonus.h"

static void	load_sprite_or_exit(t_game *game, void **img_ptr, char *path);
static void	load_sprites(t_game *game);
static void	load_player_animations(t_game *game);

void	init_game(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_map(game->map);
		error_exit("Falha na inicialização do MLX.");
	}
	win_width = game->map_width * TILE_SIZE;
	win_height = game->map_height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height, "So Long - Bonus");
	if (!game->win)
	{
		free_game(game);
		error_exit("Falha na criação da janela.");
	}
	load_sprites(game);
	load_player_animations(game);
	init_enemies(game);
	game->moves = 0;
	game->collected = 0;
	game->current_frame = 0;
	game->frame_counter = 0;
	game->game_over = 0;
	render_game(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_loop_hook(game->mlx, game_loop, game);
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
		error_exit("Falha ao carregar textura. Verifique o caminho ou arquivo XPM.");
	}
}

static void	load_sprites(t_game *game)
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

static void	load_player_animations(t_game *game)
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
