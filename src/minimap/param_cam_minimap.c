/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_cam_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:49:12 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 11:57:29 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	mm_tile_size(t_data *d)
{
	if (d->gfx->cam.tile_size > 0)
		return (d->gfx->cam.tile_size);
	return (8);
}

int	mm_off_x(t_data *d)
{
	return (d->gfx->cam.x_offset);
}

int	mm_off_y(t_data *d)
{
	return (d->gfx->cam.y_offset);
}

/* couleur selon le char de la map */
int	mm_color_for_cell(t_data *d, char c)
{
	if (c == '1')
		return (DARKGRAY);
	if (c == '0')
		return (BEIGE);
	if (c == ' ')
		return (BLACK);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (d->game->elements.rgb_floor);
	return (GRAY);
}
