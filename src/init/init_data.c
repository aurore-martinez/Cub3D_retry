/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:35:49 by eieong            #+#    #+#             */
/*   Updated: 2025/11/10 15:47:55 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_gfx(t_gfx *gfx)
{
	if (!gfx)
		return ;
	gfx->frame.img = NULL;
	gfx->frame.addr = NULL;
	gfx->frame.bpp = 0;
	gfx->frame.line_len = 0;
	gfx->frame.endian = 0;
	gfx->cam.tile_size = 0;
	gfx->cam.x_offset = 0;
	gfx->cam.y_offset = 0;
	gfx->cam.zoom = 1.0f;
	gfx->cam.z_scale = 1;
	gfx->cam.color = 0xFFFFFF;
}

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

/* “player” {0} */
static void	zero_player(t_vec *p)
{
	p->pos.x = 0.0;
	p->pos.y = 0.0;
	p->dir.x = 0.0;
	p->dir.y = 0.0;
	p->plane.x = 0.0;
	p->plane.y = 0.0;
}

/* init data */
bool	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("Error");
		return (false);
	}
	ft_memset(*data, 0, sizeof(t_data));
	(*data)->game = NULL;
	(*data)->gfx = NULL;
	(*data)->scr_w = SCR_W;
	(*data)->scr_h = SCR_H;
	zero_player(&(*data)->player);
	return (true);
}
