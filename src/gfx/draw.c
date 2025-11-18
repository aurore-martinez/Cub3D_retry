/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/18 16:32:00 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// if (p.x < 0 || p.x >= img->w || p.y < 0 || p.y >= img->h) ??
void	draw_pixel(t_img *img, t_point p)
{
	char	*dst;

	if (img == NULL)
		return ;
	if (img->addr == NULL)
		return ;
	if (p.x < 0 || p.y < 0)
		return ;
	dst = img->addr + (p.y * img->line_len + p.x * (img->bpp / 8));
	*(unsigned int *)dst = p.color;
}

/* draw line horizontale: p0.y fixé, x de p0.x à x1 */
void	draw_hline(t_img *img, t_pos p0, int x1, int color)
{
	t_point	p;
	int		tmp;

	if (!img || p0.y < 0)
		return ;
	if (p0.x > x1)
	{
		tmp = p0.x;
		p0.x = x1;
		x1 = tmp;
	}
	p.y = p0.y;
	p.color = color;
	while (p0.x <= x1)
	{
		p.x = p0.x;
		draw_pixel(img, p);
		p0.x++;
	}
}

/* draw line verticale: p0.x fixé, y de p0.y à y1 */
void	draw_vline(t_img *img, t_pos p0, int y1, int color)
{
	t_point	p;
	int		tmp;

	if (!img || p0.x < 0)
		return ;
	if (p0.y > y1)
	{
		tmp = p0.y;
		p0.y = y1;
		y1 = tmp;
	}
	p.x = p0.x;
	p.color = color;
	while (p0.y <= y1)
	{
		p.y = p0.y;
		draw_pixel(img, p);
		p0.y++;
	}
}

/* = draw vline mieux pour raycast */
void	draw_col(t_data *d, int x, int start, int end, int color)
{
	int		y;
	t_point	p;

	if (!d || x < 0 || x >= d->scr_w)
		return ;
	if (start < 0)
		start = 0;
	if (end >= d->scr_h)
		end = d->scr_h - 1;
	if (start > end)
		return ;
	y = start;
	while (y <= end)
	{
		p.x = x;
		p.y = y;
		p.color = color;
		draw_pixel(&d->gfx->frame, p);
		y++;
	}
}

void	request_redraw(t_data *d)
{
	if (!d)
		return ;
	d->need_redraw = true;
}
