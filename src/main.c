/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:43:03 by eieong            #+#    #+#             */
/*   Updated: 2025/11/04 14:23:21 by eieong           ###   ########.fr       */
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
	t_data	*data;

	game = NULL;
	data = NULL;
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

	print_game(game);
	if (!init_data(&data))
		return (clean_game(game), 1);
	if (!init_player_from_game(data, game))
		return (clean_data(data), 1);

	print_player_data(data);

	if (!init_mlx(data))
		return (clean_data(data), 1);

	render_frame(data);
	mlx_key_hook(data->gfx.win, on_key_press, data);
	mlx_hook(data->gfx.win, 17, 0, on_destroy_event, data);
	mlx_loop(data->gfx.mlx);

	clean_data(data); // j'ai change clean game pour clean data
	return (0);
}
