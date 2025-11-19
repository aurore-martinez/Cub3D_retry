/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:34:10 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 13:47:59 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* dessine une cell*/
static void	draw_minimap_cell(t_img *img, t_point cell, int size)
{
	int		i;
	int		j;
	t_point	p;

	if (!img || size <= 0)
		return ;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			p.x = cell.x + i;
			p.y = cell.y + j;
			p.color = cell.color;
			draw_pixel(img, p);
			i++;
		}
		j++;
	}
}

/* debug: print full minimap player computed positions
printf("FULL: ts=%d off=(%d,%d) p=(%.3f,%.3f) cx=%d cy=%d\n",
ts, mm_off_x(d), mm_off_y(d), d->player.pos.x, d->player.pos.y, cx, cy); */

/* r = ft_max(1, ts/3); // essayer avec ca plutot radius 1 pixel
quand tile tres petit

c => center : position pixel du centre (joueur).
rel => va de -radius a +radius (distance horiz/vert par rapport au centre). */

/* petit cercle rempli pour le joueur */
static void	draw_minimap_player(t_data *d)
{
	int		ts;
	int		r;
	t_pos	c;
	t_pos	rel;
	t_point	p;

	ts = mm_tile_size(d);
	r = ts / 3;
	c = (t_pos){mm_off_x(d) + (int)(d->player.pos.y * ts + 0.5),
		mm_off_y(d) + (int)(d->player.pos.x * ts + 0.5)};
	rel.y = -r;
	while (rel.y <= r)
	{
		rel.x = -r;
		while (rel.x <= r)
		{
			if (rel.x * rel.x + rel.y * rel.y <= r * r)
			{
				p = (t_point){c.x + rel.x, c.y + rel.y, UI_PLAYER_COLOR};
				draw_pixel(&d->gfx->frame, p);
			}
			rel.x++;
		}
		rel.y++;
	}
}

/* boucle de dessin des cellules */
static void	draw_cells(t_data *d, int ts, int off_x, int off_y)
{
	int		row;
	int		col;
	char	c;
	t_point	p;

	row = 0;
	while (row < d->game->height && d->game->map[row])
	{
		col = 0;
		while (col < d->game->width)
		{
			c = d->game->map[row][col];
			if (c != ' ')
			{
				p.x = off_x + col * ts;
				p.y = off_y + row * ts;
				p.color = mm_color_for_cell(d, c);
				draw_minimap_cell(&d->gfx->frame, p, ts);
			}
			col++;
		}
		row++;
	}
}

/* mini-map complète */
/*
x = col
y = row
*/
void	draw_minimap(t_data *d)
{
	int	ts;
	int	off_x;
	int	off_y;

	if (!d || !d->game || !d->game->map)
		return ;
	ts = mm_tile_size(d);
	off_x = mm_off_x(d);
	off_y = mm_off_y(d);
	draw_cells(d, ts, off_x, off_y);
	draw_minimap_player(d);
	draw_minimap_fov(d);
}

/* ligne horizontale jaune au centre de la mini-map */
/* static void	draw_minimap_horizon(t_data *d)
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
} */
