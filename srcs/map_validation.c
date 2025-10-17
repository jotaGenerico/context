/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:12:48 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/13 20:12:52 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_map(t_game *game)
{
	check_retangularity(game);
	check_walls(game);
	check_components(game);
	check_path(game);
}

void	check_components(t_game *game)
{
	int	i;
	int	j;

	game->collectibles = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			count_and_locate(game, i, j);
			j++;
		}
		i++;
	}
}
