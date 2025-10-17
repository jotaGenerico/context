/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:02:43 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/08 10:08:42 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_extension(char *map_path);

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./so_long_bonus <mapa.ber>");
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
		error_exit("Map file name is too short.");
	if (ft_strncmp(map_path + len - 4, ".ber", 4) != 0)
		error_exit("Map file must have a .ber extension.");
}
