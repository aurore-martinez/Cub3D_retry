/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:22:12 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 14:26:14 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* dessine une cell*/
void	draw_minimap_cell(t_img *img, t_point cell, int size)
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

void	draw_player_disc(t_img *img, t_pos center, int radius, int color)
{
	int		dy;
	int		dx;
	int		r2;
	t_point	p;

	if (!img || radius <= 0)
		return ;
	r2 = radius * radius;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= r2)
			{
				p = (t_point){center.x + dx, center.y + dy, color};
				draw_pixel(img, p);
			}
			dx++;
		}
		dy++;
	}
}
