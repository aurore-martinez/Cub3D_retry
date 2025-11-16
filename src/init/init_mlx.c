/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:30:03 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/16 17:26:54 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	set_texture(t_data *data)
{
	int	width;
	int	height;

	printf("Loading textures:\n");
	printf("  NO: %s\n", data->game->elements.path_north);
	data->gfx->texture.north = mlx_xpm_file_to_image(data->gfx->mlx,
			data->game->elements.path_north, &width, &height);
	printf("  North loaded: %p (size: %dx%d)\n", data->gfx->texture.north, width, height);

	printf("  SO: %s\n", data->game->elements.path_south);
	data->gfx->texture.south = mlx_xpm_file_to_image(data->gfx->mlx,
			data->game->elements.path_south, &width, &height);
	printf("  South loaded: %p (size: %dx%d)\n", data->gfx->texture.south, width, height);

	printf("  EA: %s\n", data->game->elements.path_east);
	data->gfx->texture.east = mlx_xpm_file_to_image(data->gfx->mlx,
			data->game->elements.path_east, &width, &height);
	printf("  East loaded: %p (size: %dx%d)\n", data->gfx->texture.east, width, height);

	printf("  WE: %s\n", data->game->elements.path_west);
	data->gfx->texture.west = mlx_xpm_file_to_image(data->gfx->mlx,
			data->game->elements.path_west, &width, &height);
	printf("  West loaded: %p (size: %dx%d)\n", data->gfx->texture.west, width, height);

	if (!data->gfx->texture.north || !data->gfx->texture.south
		|| !data->gfx->texture.west || !data->gfx->texture.east)
	{
		printf("ERROR: Some textures failed to load!\n");
		return (false);
	}
	printf("All textures loaded successfully!\n");
	return (true);
}

/* set camera */
bool	set_camera(t_data *data)
{
	int		max_map_dim;
	int		minimap_size;
	int		minimap_w;
	int		minimap_h;

	if (!data || !data->game || !data->gfx)
		return (false);
	minimap_size = 250;
	// minimap_size = SCR_W / 4;
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
	gfx->cam.zoom = 1.0f; // init mais non used
	gfx->cam.z_scale = 1; // init mais non used
	gfx->cam.color = 0xFFFFFF; // init mais non used
	gfx->texture.north = NULL;
	gfx->texture.south = NULL;
	gfx->texture.west = NULL;
	gfx->texture.east = NULL;
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
