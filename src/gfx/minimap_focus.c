/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_focus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 10:09:57 by aumartin         ###   ########.fr       */
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

static void	draw_focus_cell(t_data *d, int x, int y, int size, int color)
{
	int	i;
	int	j;
	t_point	p;

	if (size <= 0 || d == NULL)
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
			draw_pixel(&d->gfx->frame, p);
			i++;
		}
		j++;
	}
}

static void	draw_focus_player(t_data *d, int ts, int crop_x, int crop_y,
	int start_row, int start_col)
{
	int		player_screen_x;
	int		player_screen_y;
	int		cx;
	int		cy;
	int		pr;
	int		px;
	int		py;
	t_point	p;

	if (d == NULL)
		return ;
	player_screen_x = (int)(d->player.pos.y) - start_col;
	player_screen_y = (int)(d->player.pos.x) - start_row;
	cx = crop_x + player_screen_x * ts + ts / 2;
	cy = crop_y + player_screen_y * ts + ts / 2;
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
	int		start_row;
	int		start_col;
	int		end_row;
	int		end_col;
	int		crop_x;
	int		crop_y;
	int		row;
	int		col;
	int		base_ts;
	double	zoom;

	if (d == NULL || d->game == NULL || d->game->map == NULL)
		return ;
	r = 8;
	base_ts = mm_tile_size(d);
	zoom = mf_get_zoom_factor(d, r, base_ts);
	ts = (int)(base_ts * zoom);
	if (ts <= 0)
		ts = 1;
	p_row = (int)(d->player.pos.x);
	p_col = (int)(d->player.pos.y);
	start_row = p_row - r;
	if (start_row < 0)
		start_row = 0;
	end_row = p_row + r;
	if (end_row >= d->game->height)
		end_row = d->game->height - 1;
	start_col = p_col - r;
	if (start_col < 0)
		start_col = 0;
	end_col = p_col + r;
	if (end_col >= d->game->width)
		end_col = d->game->width - 1;
	crop_x = 20;
	crop_y = 20;
	row = start_row;
	while (row <= end_row)
	{
		col = start_col;
		while (col <= end_col)
		{
			if (d->game->map[row][col] != ' ')
			{
			draw_focus_cell(d, crop_x + (col - start_col) * ts,
				crop_y + (row - start_row) * ts, ts,
				mf_color_for_cell(d, d->game->map[row][col]));
			}
			col++;
		}
		row++;
	}
	draw_focus_player(d, ts, crop_x, crop_y, start_row, start_col);
	draw_minimap_fov(d);
}
