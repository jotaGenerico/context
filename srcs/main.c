#include "so_long.h"

static void	check_extension(char *map_path);

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		if (argc < 2)
			error_exit("Erro\nFaltando argumento de mapa. Uso: ./so_long <mapa.ber>");
		else
			error_exit("Erro\nMuitos argumentos fornecidos. Uso: ./so_long <mapa.ber>");
	}
	check_extension(argv[1]);
	ft_bzero(&game, sizeof(t_game));
	read_map(&game, argv[1]);
	validate_map(&game);
	init_game(&game);
	return (0);
}

static void	check_extension(char *map_path)
{
	size_t	len;

	len = ft_strlen(map_path);
	if (len < 4)
		error_exit("Erro\nNome do arquivo de mapa é muito curto.");
	if (ft_strncmp(map_path + len - 4, ".ber", 4) != 0)
		error_exit("Erro\nO arquivo de mapa deve ter a extensão .ber.");
}
