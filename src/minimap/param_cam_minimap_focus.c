/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_cam_minimap_focus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:57:16 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 11:57:36 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
