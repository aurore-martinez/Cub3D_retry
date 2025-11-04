/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:42 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 11:38:42 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	change_view(int key, t_engine *engine)
{
	if (key == KEY_LEFT)
		engine->camera.x_offset -= VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_RIGHT)
		engine->camera.x_offset += VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_UP)
		engine->camera.y_offset -= VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_DOWN)
		engine->camera.y_offset += VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_PLUS)
		engine->camera.zoom *= ZOOM_FACTOR;
	else if (key == KEY_MINUS)
		engine->camera.zoom /= ZOOM_FACTOR;
	else if (key == KEY_1)
		engine->camera.z_scale += 1;
	else if (key == KEY_2)
		engine->camera.z_scale -= 1;
	else if (key == KEY_9)
		engine->camera.tile_size += 1;
	else if (key == KEY_0)
		engine->camera.tile_size -= 1;
}

void	change_color(int key, t_engine *engine)
{
	if (key == KEY_Q)
		engine->camera.color = 0xFF0000;
	else if (key == KEY_W)
		engine->camera.color = 0x00FF00;
	else if (key == KEY_E)
		engine->camera.color = 0x0000FF;
	else if (key == KEY_R)
		engine->camera.color = 0xFFFF00;
	else if (key == KEY_T)
		engine->camera.color = 0xFF00FF;
	else if (key == KEY_Y)
		engine->camera.color = 0x00FFFF;
	else if (key == KEY_A)
		engine->camera.color = 0xFFFFFF;
	else if (key == KEY_S)
		engine->camera.color = 0x888888;
	else if (key == KEY_D)
		engine->camera.color = 0x000000;
	else if (key == KEY_F)
		engine->camera.color = 0xFF8800;
	else if (key == KEY_G)
		engine->camera.color = 0x8800FF;
	else if (key == KEY_H)
		engine->camera.color = 0x00FF88;
}

int	get_z_range(t_map *map)
{
	int	x;
	int	y;
	int	min_z;
	int	max_z;

	y = 0;
	min_z = map->grid[0][0].z;
	max_z = map->grid[0][0].z;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x].z < min_z)
				min_z = map->grid[y][x].z;
			if (map->grid[y][x].z > max_z)
				max_z = map->grid[y][x].z;
			x++;
		}
		y++;
	}
	return (max_z - min_z);
}

int	determine_z_scale(t_map *map)
{
	int	range;

	range = get_z_range(map);
	if (map->width <= 30 && map->height <= 30 && range <= 15)
		return (5);
	else if (range == 0)
		return (30);
	else if (range < 5)
		return (25);
	else if (range < 15)
		return (20);
	else if (range < 30)
		return (15);
	else if (range < 60)
		return (10);
	else
		return (5);
}

int	determine_tile_size(t_map *map)
{
	int	width;
	int	height;

	width = map->width;
	height = map->height;
	if (width <= 30 && height <= 30)
		return (20);
	else if (width > 150 || height > 150)
		return (5);
	else if (width > 100 || height > 100)
		return (10);
	else if (width > 50 || height > 50)
		return (15);
	else
		return (20);
}
