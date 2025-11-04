/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:40:03 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 11:00:53 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
WIP copie colle de fdf a adapter pour Cub
*/

void	render_map(t_engine *engine)
{
	int	x;
	int	y;

	mlx_clear_window(engine->mlx, engine->window);
	ft_bzero(engine->image.addr_ptr, WIN_WIDTH * WIN_HEIGHT * 4);
	y = 0;
	while (y < engine->map.height)
	{
		x = 0;
		while (x < engine->map.width)
		{
			draw_connections(engine, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(engine->mlx, engine->window,
		engine->image.img_ptr, 0, 0);
}
void	init_camera(t_camera *camera)
{
	camera->zoom = 1.0;
	camera->tile_size = 20;
	camera->z_scale = 1;
	camera->x_offset = WIN_WIDTH / 2;
	camera->y_offset = WIN_HEIGHT / 2;
	camera->color = 0xFFFFFF;
}

void	init_engine(t_engine *engine, char *filename)
{
	int	pixel_bits;
	int	line_len;
	int	endian;

	parse_map(filename, &engine->map);
	engine->mlx = mlx_init();
	if (!engine->mlx)
		error_message("[MLX ERROR]: can't init mlx!\n", 1);
	engine->window = mlx_new_window(engine->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	engine->image.img_ptr = mlx_new_image(engine->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!engine->window || !engine->image.img_ptr)
	{
		mlx_destroy_image(engine->mlx, engine->image.img_ptr);
		mlx_destroy_window(engine->mlx, engine->window);
		error_message("[MLX ERROR]: failed to create window/image!\n", 1);
	}
	engine->image.addr_ptr = mlx_get_data_addr(engine->image.img_ptr,
			&pixel_bits, &line_len, &endian);
	engine->image.pixel_bits = pixel_bits;
	engine->image.line_len = line_len;
	engine->image.endian = endian;
	init_camera(&engine->camera);
	engine->camera.z_scale = determine_z_scale(&engine->map);
	engine->camera.tile_size = determine_tile_size(&engine->map);
}
