/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessorize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:00:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 10:55:44 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Croix */
void	draw_crosshair(t_data *d)
{
	int	midy;
	int	midx;

	if (!d || !d->gfx)
		return ;
	midy = d->scr_h / 2;
	midx = d->scr_w / 2;
	draw_hline(&d->gfx->frame, (t_pos){midx - 15, midy}, midx - 5,
		UI_CROSSHAIR_COLOR);
	draw_hline(&d->gfx->frame, (t_pos){midx + 5, midy}, midx + 15,
		UI_CROSSHAIR_COLOR);
	draw_vline(&d->gfx->frame, (t_pos){midx, midy - 15}, midy - 5,
		UI_CROSSHAIR_COLOR);
	draw_vline(&d->gfx->frame, (t_pos){midx, midy + 5}, midy + 15,
		UI_CROSSHAIR_COLOR);
}
