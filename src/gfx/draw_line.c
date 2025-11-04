/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 11:08:10 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	Tracer une ligne droite entre 2 pts sur l'écran, pixel par pixel (Bresenham)
	- L'init de Bresenham (init_bresenham)
	- Le placement d'un pixel (draw_pixel)
	- Update du pixel (update_position)
	- Boucle qui trace toute la ligne (draw_line)
*/

static void	init_bresenham(t_bresenham *b, t_point a, t_point b_point)
{
	b->dx = abs(b_point.x - a.x);
	b->dy = abs(b_point.y - a.y);
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

static void	draw_pixel(t_engine *engine, t_point a)
{
	int		color;
	char	*dst;

	if (a.color != -1)
		color = a.color;
	else
		color = engine->camera.color;
	if (a.x < 0 || a.x >= WIN_WIDTH || a.y < 0 || a.y >= WIN_HEIGHT)
		return ;
	dst = engine->image.addr_ptr
		+ (a.y * engine->image.line_len + a.x * (engine->image.pixel_bits / 8));
	*(unsigned int *)dst = color;
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

void	draw_line(t_engine *engine, t_point a, t_point b_point)
{
	t_bresenham	b;

	init_bresenham(&b, a, b_point);
	while (1)
	{
		draw_pixel(engine, a);
		if (a.x == b_point.x && a.y == b_point.y)
			break ;
		update_position(&b, &a);
	}
}

void	draw_connections(t_engine *engine, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1 = get_projected_point(engine->map.grid[y][x], engine);
	if (x < engine->map.width - 1)
	{
		p2 = get_projected_point(engine->map.grid[y][x + 1], engine);
		draw_line(engine, p1, p2);
	}
	if (y < engine->map.height - 1)
	{
		p2 = get_projected_point(engine->map.grid[y + 1][x], engine);
		draw_line(engine, p1, p2);
	}
}
