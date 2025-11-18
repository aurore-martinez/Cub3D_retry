/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/18 15:17:52 by aumartin         ###   ########.fr       */
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

/* draw line horizontale */
void	draw_hline(t_img *img, int y, int x0, int x1, int color)
{
	t_point	p;

	if (img == NULL)
		return ;
	if (y < 0)
		return ;
	if (x0 > x1)
		ft_swap(&x0, &x1);
	p.y = y;
	p.color = color;
	while (x0 <= x1)
	{
		p.x = x0;
		draw_pixel(img, p);
		x0++;
	}
}

/* draw line verticale */
void	draw_vline(t_img *img, int x, int y0, int y1, int color)
{
	t_point	p;

	if (img == NULL)
		return ;
	if (x < 0)
		return ;
	if (y0 > y1)
		ft_swap(&y0, &y1);
	p.x = x;

	p.color = color;
	while (y0 <= y1)
	{
		p.y = y0;
		draw_pixel(img, p);
		y0++;
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

/* Bresenham line algorithm */
void	draw_line(t_img *img, t_point p0, t_point p1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = ft_abs(p1.x - p0.x);
	dy = ft_abs(p1.y - p0.y);
	sx = (p0.x < p1.x) ? 1 : -1;
	sy = (p0.y < p1.y) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		draw_pixel(img, p0);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
		}
	}
}
