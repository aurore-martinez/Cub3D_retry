/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:34:10 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/10 15:33:02 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* paramètres mini-map */
static int	mm_tile_size(t_data *d)
{
	if (d->gfx->cam.tile_size > 0)
		return (d->gfx->cam.tile_size);
	return (8);
}

static int	mm_off_x(t_data *d)
{
	return (d->gfx->cam.x_offset);
}

static int	mm_off_y(t_data *d)
{
	return (d->gfx->cam.y_offset);
}

/* couleur selon le char de la map */
static int	mm_color_for_cell(char c)
{
	if (c == '1')
		return (RGB(50, 50, 50));
	if (c == '0')
		return (RGB(180, 180, 180));
	if (c == ' ')
		return (RGB(0, 0, 0));
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (RGB(140, 200, 255));
	return (RGB(100, 100, 100));
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int		i;
	int		j;
	t_point	p;

	if (img == NULL)
		return ;
	if (size <= 0)
		return ;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			p.x = x + i;
			p.y = y + j;
			p.z = 0;
			p.color = color;
			draw_pixel(img, p);
			i++;
		}
		j++;
	}
}

/* dessine 1 cellule */
static void	draw_minimap_cell(t_data *d, int row, int col, int color)
{
	int	x;
	int	y;
	int	ts;

	ts = mm_tile_size(d);
	x = mm_off_x(d) + col * ts;
	y = mm_off_y(d) + row * ts;
	draw_square(&d->gfx->frame, x, y, ts, color);
}

/* petit cercle rempli pour le joueur */
static void	draw_minimap_player(t_data *d)
{
	int		ts;
	int		r;
	int		cx;
	int		cy;
	int		x;
	int		y;
	t_point	p;

	ts = mm_tile_size(d);
	r = ts / 3; /* rayon (1/3 d'une case) */
	/* position joueur (col = y, row = x) */
	cx = mm_off_x(d) + (int)(d->player.pos.y * ts + ts / 2);
	cy = mm_off_y(d) + (int)(d->player.pos.x * ts + ts / 2);

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
			{
				p.x = cx + x;
				p.y = cy + y;
				p.z = 0;
				p.color = RGB(255, 50, 50);
				draw_pixel(&d->gfx->frame, p);
			}
			x++;
		}
		y++;
	}
}

/* ligne horizontale jaune au centre de la mini-map */
static void	draw_minimap_horizon(t_data *d)
{
	int		ts;
	int		map_w;
	int		map_h;
	int		mid_y;
	int		x;
	t_point	p;

	ts = mm_tile_size(d);
	map_w = d->game->width * ts;
	map_h = d->game->height * ts;
	mid_y = mm_off_y(d) + map_h / 2;

	x = mm_off_x(d);
	while (x < mm_off_x(d) + map_w)
	{
		p.x = x;
		p.y = mid_y;
		p.z = 0;
		p.color = RGB(255, 220, 0);
		draw_pixel(&d->gfx->frame, p);
		x++;
	}
}

/* mini-map complète */
void	draw_minimap(t_data *d)
{
	int		row;
	int		col;
	int		color;
	char	c;

	if (d == NULL || d->game == NULL || d->game->map == NULL)
		return ;

	row = 0;
	while (row < d->game->height && d->game->map[row] != NULL)
	{
		col = 0;
		while (col < d->game->width)
		{
			c = d->game->map[row][col];
			color = mm_color_for_cell(c);
			draw_minimap_cell(d, row, col, color);
			col++;
		}
		row++;
	}
	draw_minimap_horizon(d);
	draw_minimap_player(d);
}
