#include "so_long.h"

static char	*read_to_str(int fd, t_game *game);

void	read_map(t_game *game, char *filename)
{
	int		fd;
	char	*map_str;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Não foi possível abrir o arquivo de mapa.");
	map_str = read_to_str(fd, game);
	close(fd);
	if (game->map_height == 0)
	{
		free(map_str);
		error_exit("O arquivo de mapa está vazio.");
	}
	game->map = ft_split(map_str, '\n');
	free(map_str);
	if (!game->map || !game->map[0])
		error_exit("Falha ao dividir o mapa (ft_split falhou).");
	game->map_width = ft_strlen(game->map[0]);
}

static char	*read_to_str(int fd, t_game *game)
{
	char	*line;
	char	*map_str;

	map_str = ft_strdup("");
	if (!map_str)
		error_exit("Falha na alocação da string inicial.");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map_str = gnl_strjoin(map_str, line);
		if (!map_str)
		{
			free(line);
			error_exit("Falha na alocação da string do mapa.");
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
