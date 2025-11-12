/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:30:03 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/12 12:23:55 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* set camera */
bool	set_camera(t_data *data)
{
	int		max_map_dim;
	int		minimap_size;
	int		minimap_w;
	int		minimap_h;

	if (!data || !data->game || !data->gfx)
		return (false);
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
	return (true);
}

/* init gfx */
static bool	init_gfx(t_gfx *gfx)
{
	if (!gfx)
		return (false);
	gfx->frame.img = NULL;
	gfx->frame.addr = NULL;
	gfx->frame.bpp = 0;
	gfx->frame.line_len = 0;
	gfx->frame.endian = 0;
	gfx->cam.tile_size = 8;
	gfx->cam.x_offset = 0;
	gfx->cam.y_offset = 0;
	gfx->cam.zoom = 1.0f; // init mais non used
	gfx->cam.z_scale = 1; // init mais non used
	gfx->cam.color = 0xFFFFFF; // init mais non used
	return (true);
}

/* init mlx */
bool	init_mlx(t_gfx **gfx, int w, int h, const char *title)
{
	*gfx = malloc(sizeof(t_gfx));
	if (!(*gfx))
	{
		perror("Error");
		return (false);
	}
	init_gfx(*gfx);
	(*gfx)->mlx = mlx_init();
	if ((*gfx)->mlx == NULL)
		return (false);
	(*gfx)->win = mlx_new_window((*gfx)->mlx, w, h, (char *)title);
	if ((*gfx)->win == NULL)
		return (false);
	(*gfx)->frame.img = mlx_new_image((*gfx)->mlx, w, h);
	if ((*gfx)->frame.img == NULL)
		return (false);
	(*gfx)->frame.addr = mlx_get_data_addr((*gfx)->frame.img,
			&(*gfx)->frame.bpp, &(*gfx)->frame.line_len,
			&(*gfx)->frame.endian);
	if ((*gfx)->frame.addr == NULL)
		return (false);
	return (true);
}
