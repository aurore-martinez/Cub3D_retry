/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_focus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/14 15:21:08 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	mf_tile_size(t_data *d)
{
	if (d && d->gfx && d->gfx->cam.tile_size > 0)
		return (d->gfx->cam.tile_size);
	return (8);
}

static int	mf_off_x(t_data *d)
{
	if (d && d->gfx)
		return (d->gfx->cam.x_offset);
	return (0);
}

static int	mf_off_y(t_data *d)
{
	if (d && d->gfx)
		return (d->gfx->cam.y_offset);
	return (0);
}

static int	mf_color_for_cell(char c)
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
			p.z = 0;
			p.color = color;
			draw_pixel(&d->gfx->frame, p);
			i++;
		}
		j++;
	}
}

static void	draw_focus_player(t_data *d, int ts)
{
	int		abs_x;
	int		abs_y;
	int		cx;
	int		cy;
	int		pr;
	int		px;
	int		py;
	t_point	p;

	if (d == NULL)
		return ;
	abs_x = mf_off_x(d) + (int)(d->player.pos.y * ts + 0.5);
	abs_y = mf_off_y(d) + (int)(d->player.pos.x * ts + 0.5);
	cx = abs_x;
	cy = abs_y;
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
				p.z = 0;
				p.color = RGB(255, 50, 50);
				draw_pixel(&d->gfx->frame, p);
			}
			px++;
		}
		py++;
	}
}

/* minimap focus - crop 11x11 using absolute coordinates */
void	draw_minimap_focus(t_data *d)
{
	int	ts;
	int	r;
	int	p_row;
	int	p_col;
	int	start_row;
	int	start_col;
	int	end_row;
	int	end_col;
	int	crop_x;
	int	crop_y;
	int	row;
	int	col;

	if (d == NULL || d->game == NULL || d->game->map == NULL)
		return ;
	r = 15;
	ts = mf_tile_size(d);
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
	crop_x = mf_off_x(d) + start_col * ts;
	crop_y = mf_off_y(d) + start_row * ts;
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
					mf_color_for_cell(d->game->map[row][col]));
			}
			col++;
		}
		row++;
	}
	draw_focus_player(d, ts);
}
