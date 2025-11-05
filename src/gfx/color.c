/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:20:26 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 12:46:53 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* check limit RGB entre 0 et 255 */
static int	limit_rgb_value(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

/* Amke col from RGB */
int	color_rgb(int r, int g, int b)
{
	r = limit_rgb_value(r);
	g = limit_rgb_value(g);
	b = limit_rgb_value(b);
	return ((r << 16) | (g << 8) | b);
}

/* convertit la col pour la minilibX */
int	color_for_mlx(void *mlx_ptr, int color)
{
	return (mlx_get_color_value(mlx_ptr, color));
}

/* TODO a utiliser et implem  */
/* void	draw(void *mlx, void *win)
{
	int	col;
	int	good;

	col = color_rgb(200, 100, 50);
	good = color_for_mlx(mlx, col);
	mlx_pixel_put(mlx, win, 100, 100, good);
	mlx_pixel_put(mlx, win, 120, 120, color_for_mlx(mlx, BLUE));
} */
