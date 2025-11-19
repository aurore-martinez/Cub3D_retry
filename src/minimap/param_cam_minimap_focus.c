/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_cam_minimap_focus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:57:16 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 14:56:07 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Calcule le facteur de zoom en fonction de la taille de la carte */
static double	get_zoom_by_map_size(t_data *d)
{
	int	max_dim;

	max_dim = d->game->width;
	if (d->game->height > max_dim)
		max_dim = d->game->height;
	if (max_dim > 100)
		return (3.0);
	if (max_dim > 60)
		return (2.5);
	if (max_dim > 30)
		return (2.0);
	return (1.5);
}

/* Calcule le facteur de zoom optimal pour éviter débordement */
static double	mf_get_zoom_factor(t_data *d, int r, int base_ts)
{
	int		crop_w;
	int		crop_h;
	double	zoom;
	int		available_w;
	int		available_h;

	zoom = get_zoom_by_map_size(d);
	available_w = d->scr_w - 40;
	available_h = d->scr_h - 40;
	crop_w = (r * 2 + 1) * base_ts * zoom;
	crop_h = (r * 2 + 1) * base_ts * zoom;
	while ((crop_w > available_w || crop_h > available_h) && zoom > 1.0)
	{
		zoom -= 0.1;
		crop_w = (r * 2 + 1) * base_ts * zoom;
		crop_h = (r * 2 + 1) * base_ts * zoom;
	}
	if (zoom < 1.0)
		zoom = 1.0;
	return (zoom);
}

/* Taille d'une tuile en mode focus (base_ts * zoom), clampée à >= 1 */
int	mf_tile_size(t_data *d)
{
	int		base_ts;
	double	zoom;
	int		ts;

	if (!d)
		return (1);
	base_ts = mm_tile_size(d);
	zoom = mf_get_zoom_factor(d, 8, base_ts);
	ts = (int)(base_ts * zoom);
	if (ts <= 0)
		ts = 1;
	return (ts);
}

/* Décalage X (pixels) du coin haut-gauche du viewport focus */
/* Même logique de bord que le dessin: fenêtre peut se réduire près des bords */
int	mf_off_x(t_data *d)
{
	int	ts;
	int	r;
	int	p_col;
	int	start_col;

	if (!d || !d->game)
		return (20);
	ts = mf_tile_size(d);
	r = 8;
	p_col = (int)d->player.pos.y;
	start_col = p_col - r;
	if (start_col < 0)
		start_col = 0;
	return (20 - start_col * ts);
}

/* Décalage Y (pixels) du coin haut-gauche du viewport focus */
int	mf_off_y(t_data *d)
{
	int	ts;
	int	r;
	int	p_row;
	int	start_row;

	if (!d || !d->game)
		return (20);
	ts = mf_tile_size(d);
	r = 8;
	p_row = (int)d->player.pos.x;
	start_row = p_row - r;
	if (start_row < 0)
		start_row = 0;
	return (20 - start_row * ts);
}
