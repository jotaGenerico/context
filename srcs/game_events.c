#include "so_long.h"

static void	move_player(t_game *game, int dx, int dy);

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_game(game);
	else if (keycode == W_KEY)
		move_player(game, 0, -1);
	else if (keycode == S_KEY)
		move_player(game, 0, 1);
	else if (keycode == A_KEY)
		move_player(game, -1, 0);
	else if (keycode == D_KEY)
		move_player(game, 1, 0);
	return (0);
}

static void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	target_tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	target_tile = game->map[new_y][new_x];
	if (target_tile == '1')
		return;
	if (target_tile == 'E')
	{
		if (game->collected == game->collectibles)
		{
			game->moves++;
			ft_printf("Movimentos: %d\n", game->moves);
			ft_printf("Parabéns! Você ganhou em %d movimentos!\n", game->moves);
			close_game(game);
		}
		return ;
	}
	if (target_tile == 'C')
	{
		game->collected++;
		game->map[new_y][new_x] = '0';
	}
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Movimentos: %d\n", game->moves);
	render_game(game);
}
