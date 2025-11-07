/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:43:03 by eieong            #+#    #+#             */
/*   Updated: 2025/11/07 11:12:57 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	init_game(t_game **game, char *filename)
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
		free(*game);
		*game = NULL;
		return (false);
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

static bool	parsing(char *file, t_game **game)
{
	if (!init_game(game, file))
		return (false);
	if (!parse_game_info(*game))
		return (false);
	if (!check_map(*game))
		return (false);
	print_map((*game)->map);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 2)
		exit_error("Usage: ./cub3d [map_file].cub");
	if (!check_filename(argv[1]))
		return (1);
	if (!init_data(&data))
		return (1);
	if (!parsing(argv[1], &data->game))
		return (clean_data(data), 1);
	// print_game(game);
	if (!init_player_from_game(data))
		return (clean_data(data), 1);

	print_player_data(data);


	if (!init_mlx(&data->gfx, data->scr_w, data->scr_h, "cub3D"))
		return (clean_data(data), 1);

	render_frame(data);
	// mlx_key_hook(data->gfx->win, on_key_press, data);
	mlx_hook(data->gfx->win, KeyPress, KeyPressMask, on_key_press, data);
	mlx_hook(data->gfx->win, DestroyNotify, 0, on_destroy_event, data);
	mlx_loop(data->gfx->mlx);

	clean_data(data); // j'ai change clean game pour clean data
	return (0);
}
