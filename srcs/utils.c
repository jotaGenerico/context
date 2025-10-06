#include "../includes/so_long.h"

char	**copy_map(char **map, int height)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (i > 0)
			{
				i--;
				free(map_copy[i]);
			}
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[height] = NULL;
	return (map_copy);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_game(t_game *game)
{
	int	i;

	if (game->mlx)
	{
		i = 0;
		while (i < TOTAL_SPRITES)
		{
			if (game->sprites[i].img)
				mlx_destroy_image(game->mlx, game->sprites[i].img);
			i++;
		}
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
	free_map(game->map);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

int	close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	exit(0);
	return (0);
}
