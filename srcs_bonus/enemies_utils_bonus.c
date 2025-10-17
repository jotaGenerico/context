/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:25:02 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 11:25:07 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_enemies(t_game *game)
{
	t_enemy	*current;
	t_enemy	*next;

	current = game->enemies;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	game->enemies = NULL;
}
