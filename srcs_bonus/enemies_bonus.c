#include "so_long_bonus.h"

void	add_enemy(t_game *game, int x, int y)
{
	t_enemy	*new_enemy;
	t_enemy	*current;

	new_enemy = malloc(sizeof(t_enemy));
	if (!new_enemy)
		return ;
	new_enemy->x = x;
	new_enemy->y = y;
	new_enemy->direction = 1;
	new_enemy->next = NULL;
	if (!game->enemies)
		game->enemies = new_enemy;
	else
	{
		current = game->enemies;
		while (current->next)
			current = current->next;
		current->next = new_enemy;
	}
	game->enemy_count++;
}

void	init_enemies(t_game *game)
{
	int	i;
	int	j;

	game->enemies = NULL;
	game->enemy_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == ENEMY_CHAR)
			{
				add_enemy(game, j, i);
				game->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

static void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	new_x;
	int	new_y;

	new_x = enemy->x + enemy->direction;
	new_y = enemy->y;
	if (game->map[new_y][new_x] == '1' || game->map[new_y][new_x] == 'E')
		enemy->direction *= -1;
	else
		enemy->x = new_x;
}

void	update_enemies(t_game *game)
{
	static int	counter = 0;
	t_enemy		*enemy;

	counter++;
	if (counter < ENEMY_SPEED)
		return ;
	counter = 0;
	enemy = game->enemies;
	while (enemy)
	{
		move_enemy(game, enemy);
		enemy = enemy->next;
	}
}

int	check_enemy_collision(t_game *game)
{
	t_enemy	*enemy;

	enemy = game->enemies;
	while (enemy)
	{
		if (enemy->x == game->player_x && enemy->y == game->player_y)
			return (1);
		enemy = enemy->next;
	}
	return (0);
}

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
