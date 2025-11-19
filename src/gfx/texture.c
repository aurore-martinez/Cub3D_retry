/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:15:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:27 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Récupère la couleur d'un pixel dans une texture */
int	get_texture_pixel(void *img, int x, int y)
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		offset;

	if (!img)
		return (0);
	if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
		return (0);
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	if (!addr)
		return (0);
	offset = y * line_len + x * (bpp / 8);
	return (*(int *)(addr + offset));
}

/* Choisit la texture selon la direction du mur */
void	*select_texture(t_data *d, t_dda *ray, int side)
{
	if (side == 0)
	{
		if (ray->ray_col < 0)
			return (d->gfx->texture.west);
		else
			return (d->gfx->texture.east);
	}
	else
	{
		if (ray->ray_row < 0)
			return (d->gfx->texture.north);
		else
			return (d->gfx->texture.south);
	}
}

/* Calcule la position exacte où le rayon touche le mur (0.0 à 1.0) */
double	get_wall_x(t_data *d, t_dda *ray, double perp, int side)
{
	double	wall_x;

	if (side == 0)
		wall_x = d->player.pos.x + perp * ray->ray_row;
	else
		wall_x = d->player.pos.y + perp * ray->ray_col;
	wall_x -= floor(wall_x);
	return (wall_x);
}

/* Calcule la coordonnée X dans la texture */
int	get_texture_x(t_dda *ray, double wall_x, int side)
{
	int	tex_x;

	tex_x = (int)(wall_x * TEX_SIZE);
	if ((side == 0 && ray->ray_col > 0) || (side == 1 && ray->ray_row < 0))
		tex_x = TEX_SIZE - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEX_SIZE)
		tex_x = TEX_SIZE - 1;
	return (tex_x);
}

/* Dessine une colonne de texture sur l'écran */
void	draw_textured_col(t_data *d, int x, int top, int bot, t_tex_params *p)
{
	int		y;
	int		tex_y;
	int		color;
	t_point	pixel;
	double	step;

	if (!d || !p || !p->texture)
		return ;
	if (top > bot)
		return ;
	/* step = nombre de pixels texture par pixel écran en Y,
	   calculé à partir de la hauteur originelle (non clampée) */
	if (p->orig_line_h <= 0)
		return ;
	step = (double)TEX_SIZE / (double)p->orig_line_h;

	y = top;
	while (y <= bot)
	{
		/* position dans la portion visible de la colonne (0..line_h_draw-1) */
		tex_y = (int)(((double)(y - top) * (double)TEX_SIZE) / (double)p->orig_line_h)
				+ p->tex_y_offset;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= TEX_SIZE)
			tex_y = TEX_SIZE - 1;
		color = get_texture_pixel(p->texture, p->tex_x, tex_y);
		if (p->side == 1)
			color = darken_color(color);
		pixel.x = x;
		pixel.y = y;
		// pixel.z = 0;
		pixel.color = color;
		draw_pixel(&d->gfx->frame, pixel);
		y++;
	}
}
