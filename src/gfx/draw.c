/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 13:34:05 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* WIP copie colle de fdf a adapter pour Cub */

/* static void	init_bresenham(t_bresenham *b, t_point a, t_point b_point)
{
	b->dx = ft_abs(b_point.x - a.x);
	b->dy = ft_abs(b_point.y - a.y);
	if (a.x < b_point.x)
		b->sx = 1;
	else
		b->sx = -1;
	if (a.y < b_point.y)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dx - b->dy;
}

static void	update_position(t_bresenham *b, t_point *a)
{
	b->e2 = 2 * b->err;
	if (b->e2 > -b->dy)
	{
		b->err -= b->dy;
		a->x += b->sx;
	}
	if (b->e2 < b->dx)
	{
		b->err += b->dx;
		a->y += b->sy;
	}
}

void	draw_line(t_img *img, t_point a, t_point b_point)
{
	t_bresenham	b;

	init_bresenham(&b, a, b_point);
	while (1)
	{
		draw_pixel(img, a);
		if (a.x == b_point.x && a.y == b_point.y)
			break ;
		update_position(&b, &a);
	}
} */

void	draw_pixel(t_img *img, t_point p)
{
	char	*dst;

	if (img == NULL)
		return ;
	if (img->addr == NULL)
		return ;
	// if (p.x < 0 || p.x >= img->w || p.y < 0 || p.y >= img->h) ??
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
	p.z = 0;
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
	p.z = 0;
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
		p.z = 0;
		p.color = color;
		draw_pixel(&d->gfx->frame, p);
		y++;
	}
}
