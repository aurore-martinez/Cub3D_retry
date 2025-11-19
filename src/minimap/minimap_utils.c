/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:25:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 10:21:15 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Calcule le facteur de zoom en fonction de la taille de la carte */
double	get_zoom_by_map_size(t_data *d)
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
double	mf_get_zoom_factor(t_data *d, int r, int base_ts)
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
