/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:43:03 by eieong            #+#    #+#             */
/*   Updated: 2025/11/03 17:27:32 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	init_game(t_game **game, char *filename)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
	{
		perror("Error");
		return (false);
	}
	ft_memset(*game, 0, sizeof(t_game));
	(*game)->fd = open(filename, O_RDONLY);
	if ((*game)->fd < 0)
	{
		perror("Error");
		return (clean_game(*game, false));
	}
	return (true);
}

static bool	check_filename(char *name)
{
	if (ft_strlen(name) < 5)
	{
		print_error("Invalid file name");
		return (false);
	}
	name = name + (ft_strlen(name) - 4);
	if (ft_strncmp(name, ".cub", 4))
	{
		print_error("Wrong file extension");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (argc != 2)
		exit_error("Usage: ./cub3d [map_file].cub");
	if ((!check_filename(argv[1])) || !init_game(&game, argv[1]))
		return (1);
	if (!parse_game_info(game))
		return (clean_game(game, 1));
	if (!check_map(game))
		return (clean_game(game, 1));
	print_map(game->map);
	// minilibx-raycasting-exec
	if (!init_mlx(game))
		return (clean_game(game, 1));
	mlx_launch(game);
	// clean_game(game, 0); //useless, mlx exit() when ESC or X
	return (0);
}
