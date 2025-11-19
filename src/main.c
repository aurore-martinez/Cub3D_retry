/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:43:03 by eieong            #+#    #+#             */
/*   Updated: 2025/11/18 17:29:52 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static bool	init_3d(t_data *data)
{
	if (!init_player_from_game(data))
		return (false);
	print_player_data(data);
	if (!init_mlx(&data->gfx, data->scr_w, data->scr_h, "cub3D"))
		return (false);
	if (!set_texture(data))
	{
		printf("Error: Failed to load textures\n");
		return (false);
	}
	if (!set_camera(data))
		return (false);
	return (true);
}

static void	launch_mlx(t_data *data)
{
	render_frame(data);
	mlx_hook(data->gfx->win, KeyPress, KeyPressMask, on_key_press, data);
	mlx_hook(data->gfx->win, KeyRelease, KeyReleaseMask, on_key_release, data);
	mlx_hook(data->gfx->win, DestroyNotify, 0, on_destroy_event, data);
	mlx_hook(data->gfx->win, ButtonPress, ButtonPressMask, on_clic, data);
	mlx_hook(data->gfx->win, MotionNotify, PointerMotionMask, on_mouse, data);
	mlx_loop_hook(data->gfx->mlx, loop_hook, data);
	mlx_loop(data->gfx->mlx);
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
	if ((!parsing(argv[1], &data->game)) || !init_3d(data))
		return (clean_data(data), 1);
	launch_mlx(data);
	clean_data(data);
	return (0);
}
