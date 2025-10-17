/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:13:00 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/13 20:16:25 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*read_to_str(int fd, t_game *game);

void	read_map(t_game *game, char *filename)
{
	int		fd;
	char	*map_str;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Could not open map file.");
	map_str = read_to_str(fd, game);
	close(fd);
	if (game->map_height == 0)
	{
		free(map_str);
		error_exit("Error: Map file is empty.");
	}
	game->map = ft_split(map_str, '\n');
	free(map_str);
	if (!game->map || !game->map[0])
		error_exit("Error: Failed to split map (ft_split error).");
	game->map_width = ft_strlen(game->map[0]);
}

static char	*read_to_str(int fd, t_game *game)
{
	char	*line;
	char	*map_str;

	map_str = ft_strdup("");
	if (!map_str)
		error_exit("Error: Failed to allocate initial string.");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map_str = gnl_strjoin(map_str, line);
		if (!map_str)
		{
			free(line);
			error_exit("Error: Failed to allocate map string.");
		}
		free(line);
		game->map_height++;
	}
	return (map_str);
}

void	error_exit(char *message)
{
	if (message)
	{
		write(2, "Error\n", 6);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}
