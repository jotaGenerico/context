/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:02:25 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/13 20:08:33 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static void	handle_exit_tile(t_game *game);
static void	handle_collectible_tile(t_game *game, int x, int y);
static void	move_player(t_game *game, int dx, int dy);

int	handle_keypress(int keycode, t_game *game)
{
	if (game->game_over)
		return (0);
	if (keycode == ESC_KEY)
		close_game(game);
	else if (keycode == W_KEY || keycode == UP_KEY)
		move_player(game, 0, -1);
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		move_player(game, 0, 1);
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		move_player(game, -1, 0);
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		move_player(game, 1, 0);
	return (0);
}

static void	handle_exit_tile(t_game *game)
{
	if (game->collected == game->collectibles)
	{
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
		ft_printf("🎉 Congratulations! You won in %d moves!\n", game->moves);
		close_game(game);
	}
}

static void	handle_collectible_tile(t_game *game, int x, int y)
{
	game->collected++;
	game->map[y][x] = '0';
}

static void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	tile = game->map[new_y][new_x];
	if (tile == '1')
		return ;
	if (tile == 'E')
		return (handle_exit_tile(game));
	if (tile == 'C')
		handle_collectible_tile(game, new_x, new_y);
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_game(game);
}
