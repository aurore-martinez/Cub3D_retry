/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_focus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 10:40:57 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Changer start_col/row = crop.
Changer tile_size = zoom.
Changer offset_x/y = pan (position fixe coin sup gauche). */

static int	mf_color_for_cell(t_data *d, char c)
{
	if (c == '1')
		return (DARKGRAY);
	if (c == '0')
		return (BEIGE);
	if (c == ' ')
		return (BLACK);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (d->game->elements.rgb_floor);
	return (GRAY);
}

/* static void	draw_focus_cell(t_data *d, int x, int y, int size, int color) */
/* cell (x,y,color) -> dessine une cell size x size */
static void	draw_focus_cell(t_data *d, t_point cell, int size)
{
	int		j;
	int		i;
	t_point	p;

	if (!d || size <= 0)
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
			draw_pixel(&d->gfx->frame, p);
			i++;
		}
		j++;
	}
}

static void	draw_focus_player(t_data *d, int ts, t_pos crop, t_pos start)
{
	int		pr;
	int		px;
	int		py;
	int		cx;
	int		cy;
	double	fx;
	double	fy;
	t_point	p;

	if (!d)
		return ;
	fx = d->player.pos.y - start.y;
	fy = d->player.pos.x - start.x;
	cx = crop.x + (int)(fx * ts + 0.5);
	cy = crop.y + (int)(fy * ts + 0.5);
	pr = ts / 3;
	if (pr < 1)
		pr = 1;
	py = -pr;
	while (py <= pr)
	{
		px = -pr;
		while (px <= pr)
		{
			if (px * px + py * py <= pr * pr)
			{
				p.x = cx + px;
				p.y = cy + py;
				p.color = UI_PLAYER_COLOR;
				draw_pixel(&d->gfx->frame, p);
			}
			px++;
		}
		py++;
	}
}

/* minimap focus - crop with dynamic zoom */
void	draw_minimap_focus(t_data *d)
{
	int		ts;
	int		r;
	int		p_row;
	int		p_col;
	t_pos	start;
	t_pos	end;
	t_pos	crop;
	int		row;
	int		col;
	int		base_ts;
	double	zoom;

	if (!d || !d->game || !d->game->map)
		return ;
	r = 8;
	base_ts = mm_tile_size(d);
	zoom = mf_get_zoom_factor(d, r, base_ts);
	ts = (int)(base_ts * zoom);
	if (ts <= 0)
		ts = 1;
	p_row = (int)d->player.pos.x;
	p_col = (int)d->player.pos.y;
	start.x = p_row - r;
	if (start.x < 0)
		start.x = 0;
	end.x = p_row + r;
	if (end.x >= d->game->height)
		end.x = d->game->height - 1;
	start.y = p_col - r;
	if (start.y < 0)
		start.y = 0;
	end.y = p_col + r;
	if (end.y >= d->game->width)
		end.y = d->game->width - 1;
	crop.x = 20;
	crop.y = 20;
	row = start.x;
	while (row <= end.x)
	{
		col = start.y;
		while (col <= end.y)
		{
			if (d->game->map[row][col] != ' ')
				draw_focus_cell(
					d,
					(t_point){
						crop.x + (col - start.y) * ts,
						crop.y + (row - start.x) * ts,
						mf_color_for_cell(d, d->game->map[row][col])
					},
					ts
				);
			col++;
		}
		row++;
	}
	draw_focus_player(d, ts, crop, start);
	draw_minimap_fov(d);
}
