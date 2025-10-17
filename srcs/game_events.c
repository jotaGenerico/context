/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:13:53 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/13 20:24:13 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_exit_tile(t_game *game);
static void	handle_collectible_tile(t_game *game, int x, int y);
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

static void	handle_exit_tile(t_game *game)
{
	if (game->collected == game->collectibles)
	{
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
		ft_printf("Congratulations! You won in %d moves!\n", game->moves);
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
	char	target_tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	target_tile = game->map[new_y][new_x];
	if (target_tile == '1')
		return ;
	if (target_tile == 'E')
		return (handle_exit_tile(game));
	if (target_tile == 'C')
		handle_collectible_tile(game, new_x, new_y);
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_game(game);
}
