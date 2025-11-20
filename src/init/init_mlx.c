/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:30:03 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/20 11:26:53 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	load_tex_checked(void *mlx, char *path, void **dst)
{
	int	w;
	int	h;

	*dst = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!*dst)
		return (false);
	if (w != TEX_SIZE || h != TEX_SIZE)
	{
		print_error("Texture size mismatch");
		ft_fprintf(2, "%s (%dx%d expected %d)\n", path, w, h, TEX_SIZE);
		mlx_destroy_image(mlx, *dst);
		*dst = NULL;
		return (false);
	}
	return (true);
}

bool	set_texture(t_data *data)
{
	if (!load_tex_checked(data->gfx->mlx, data->game->elements.path_north,
			&data->gfx->texture.north))
		return (false);
	if (!load_tex_checked(data->gfx->mlx, data->game->elements.path_south,
			&data->gfx->texture.south))
		return (false);
	if (!load_tex_checked(data->gfx->mlx, data->game->elements.path_west,
			&data->gfx->texture.west))
		return (false);
	if (!load_tex_checked(data->gfx->mlx, data->game->elements.path_east,
			&data->gfx->texture.east))
		return (false);
	data->gfx->texture.width = TEX_SIZE;
	data->gfx->texture.height = TEX_SIZE;
	return (true);
}

/* set camera */
	// minimap_size = SCR_W / 4;
bool	set_camera(t_data *data)
{
	int		max_map_dim;
	int		minimap_size;
	int		minimap_w;
	int		minimap_h;

	if (!data || !data->game || !data->gfx)
		return (false);
	minimap_size = 250;
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
	data->gfx->cam.x_offset = 20;
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
	gfx->cam.show_full_minimap = false;
	gfx->texture.north = NULL;
	gfx->texture.south = NULL;
	gfx->texture.west = NULL;
	gfx->texture.east = NULL;
	gfx->texture.width = 0;
	gfx->texture.height = 0;
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
