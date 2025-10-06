#include "so_long_bonus.h"

static void	render_enemy(t_game *game, t_enemy *enemy)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->sprites[SPRITE_ENEMY].img,
		enemy->x * TILE_SIZE, enemy->y * TILE_SIZE);
}

static void	render_enemies(t_game *game)
{
	t_enemy	*enemy;

	enemy = game->enemies;
	while (enemy)
	{
		render_enemy(game, enemy);
		enemy = enemy->next;
	}
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
	static int	counter = 0;

	if (game->game_over)
		return (0);
	counter++;
	if (counter < 3000)
		return (0);
	counter = 0;
	update_animation(game);
	update_enemies(game);
	if (check_enemy_collision(game))
	{
		ft_printf("\n💀 GAME OVER! Você foi pego por um inimigo!\n");
		ft_printf("Movimentos: %d\n", game->moves);
		game->game_over = 1;
		close_game(game);
	}
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
	temp = ft_strjoin("Movimentos: ", moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, temp);
	free(temp);
	free(moves_str);
	temp = ft_strjoin("Coletados: ", collect_str);
	mlx_string_put(game->mlx, game->win, 10, 40, 0xFFFFFF, temp);
	free(temp);
	free(collect_str);
}
