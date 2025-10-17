/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:08:24 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 13:05:01 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	validate_component_counts(t_game *game, int p_count, int e_count);

void	check_retangularity(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) != (size_t)game->map_width)
		{
			free_map(game->map);
			error_exit("Map is not rectangular: "
				"rows have different lengths.");
		}
		i++;
	}
}

void	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[0][i] && game->map[game->map_height - 1][i])
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
		{
			free_map(game->map);
			error_exit("Map is not enclosed by walls "
				"on top or bottom.");
		}
		i++;
	}
	i = 1;
	while (i < game->map_height - 1)
	{
		if (game->map[i][0] != '1' ||
			game->map[i][game->map_width - 1] != '1')
		{
			free_map(game->map);
			error_exit("Map is not enclosed by walls "
				"on the sides.");
		}
		i++;
	}
}

void	count_and_locate(t_game *game, int i, int j)
{
	static int	p_count = 0;
	static int	e_count = 0;

	if (game->map[i][j] == 'P')
	{
		p_count++;
		game->player_x = j;
		game->player_y = i;
	}
	else if (game->map[i][j] == 'E')
		e_count++;
	else if (game->map[i][j] == 'C')
		game->collectibles++;
	else if (game->map[i][j] != '0' && game->map[i][j] != '1'
		&& game->map[i][j] != ENEMY_CHAR)
	{
		free_map(game->map);
		error_exit("Map contains an invalid character.");
	}
	if (i == game->map_height - 1 && j == game->map_width - 1)
		validate_component_counts(game, p_count, e_count);
}

static void	validate_component_counts(t_game *game, int p_count, int e_count)
{
	if (p_count != 1 || e_count != 1 || game->collectibles < 1)
	{
		free_map(game->map);
		error_exit("Map must contain exactly 1 'P', 1 'E', "
			"and at least 1 'C'.");
	}
}
