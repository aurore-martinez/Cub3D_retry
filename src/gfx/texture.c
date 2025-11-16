/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:15:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/16 17:42:23 by aumartin         ###   ########.fr       */
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
	if (x < 0 || x >= 32 || y < 0 || y >= 32)
		return (0);
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	if (!addr)
		return (0);
	offset = y * line_len + x * (bpp / 8);
	return (*(int *)(addr + offset));
}

/* Assombrit une couleur (divise par 2) pour les côtés */
int	darken_color(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r /= 2;
	g /= 2;
	b /= 2;
	return ((r << 16) | (g << 8) | b);
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

/* Calcule la coordonnée X dans la texture (0 à 31) */
int	get_texture_x(t_dda *ray, double wall_x, int side)
{
	int	tex_x;
	int	tex_width;

	tex_width = 32;
	tex_x = (int)(wall_x * tex_width);
	if ((side == 0 && ray->ray_col > 0) || (side == 1 && ray->ray_row < 0))
		tex_x = tex_width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	return (tex_x);
}

/* Dessine une colonne de texture sur l'écran */
void	draw_textured_col(t_data *d, int x, int top, int bot, t_tex_params *p)
{
	int		y;
	int		tex_y;
	int		color;
	t_point	pixel;
	char	*tex_addr;
	int		tex_bpp;
	int		tex_line_len;
	int		tex_endian;

	if (!d || !p || !p->texture || p->line_h <= 0 || top > bot)
		return ;
	tex_addr = mlx_get_data_addr(p->texture, &tex_bpp, &tex_line_len, &tex_endian);
	if (!tex_addr)
		return ;
	y = top;
	while (y <= bot)
	{
		tex_y = ((y - top) * p->tex_height) / p->line_h;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= p->tex_height)
			tex_y = p->tex_height - 1;
		if (p->tex_x >= 0 && p->tex_x < TEX_WIDTH && tex_y >= 0 && tex_y < TEX_HEIGHT)
			color = *(int *)(tex_addr + (tex_y * tex_line_len + p->tex_x * (tex_bpp / 8)));
		else
			color = 0xFF00FF;
		if (p->side == 1)
			color = darken_color(color);
		pixel.x = x;
		pixel.y = y;
		pixel.z = 0;
		pixel.color = color;
		draw_pixel(&d->gfx->frame, pixel);
		y++;
	}
}
