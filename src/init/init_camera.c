/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:30:03 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/12 10:00:14 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_camera(t_data *data)
{
	int		max_map_dim;
	int		minimap_size;
	int		minimap_w;
	int		minimap_h;

	if (!data || !data->game || !data->gfx)
		return ;
	minimap_size = 200;
	max_map_dim = data->game->width;
	if (data->game->height > max_map_dim)
		max_map_dim = data->game->height;
	data->gfx->cam.tile_size = minimap_size / max_map_dim;
	if (data->gfx->cam.tile_size < 4)
		data->gfx->cam.tile_size = 4;
	if (data->gfx->cam.tile_size > 20)
		data->gfx->cam.tile_size = 20;
	minimap_w = data->game->width * data->gfx->cam.tile_size;
	minimap_h = data->game->height * data->gfx->cam.tile_size;
	data->gfx->cam.x_offset = data->scr_w - minimap_w - 20;
	data->gfx->cam.y_offset = 20;
}
