/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:34:10 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 13:25:46 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_square(t_img *img, int x, int y, int size, int color)
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

/* debug: print full minimap player computed positions
printf("FULL: ts=%d off=(%d,%d) p=(%.3f,%.3f) cx=%d cy=%d\n",
ts, mm_off_x(d), mm_off_y(d), d->player.pos.x, d->player.pos.y, cx, cy); */

/* r = ft_max(1, ts/3); // essayer avec ca plutot radius 1 pixel
quand tile tres petit */

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
	r = ts / 3;
	cx = mm_off_x(d) + (int)(d->player.pos.y * ts + 0.5);
	cy = mm_off_y(d) + (int)(d->player.pos.x * ts + 0.5);

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
				p.color = UI_PLAYER_COLOR;
				draw_pixel(&d->gfx->frame, p);
			}
			x++;
		}
		y++;
	}
}

/* mini-map complète */
/*
x = col
y = row
*/
void	draw_minimap(t_data *d)
{
	t_point	p;
	char	c;

	if (d == NULL || d->game == NULL || d->game->map == NULL)
		return ;
	p.y = 0;
	while (p.y < d->game->height && d->game->map[p.y] != NULL)
	{
		p.x = 0;
		while (p.x < d->game->width)
		{
			c = d->game->map[p.y][p.x];
			if (c == ' ')
			{
				p.x++;
				continue ;
			}
			p.color = mm_color_for_cell(d, c);
			draw_minimap_cell(d, p.y, p.x, p.color);
			p.x++;
		}
		p.y++;
	}
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
