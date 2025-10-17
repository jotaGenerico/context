/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:13:35 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/13 20:21:13 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_extension(char *map_path);

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		if (argc < 2)
			error_exit("Error\nMissing map argument. Usage:"
				" ./so_long <map.ber>");
		else
			error_exit("Error\nToo many arguments provided. Usage:"
				" ./so_long <map.ber>");
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
		error_exit("Error\nMap file name is too short.");
	if (ft_strncmp(map_path + len - 4, ".ber", 4) != 0)
		error_exit("Error\nMap file must have the .ber extension.");
}
