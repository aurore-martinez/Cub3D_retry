/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:00:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/26 14:55:42 by aumartin         ###   ########.fr       */
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

/*
Plus sombre (≈30%): r = (r * 3) / 10; g = (g * 3) / 10; b = (b * 3) / 10;
Très sombre (≈15%): r >>= 3; g >>= 3; b >>= 3; (perte de nuance)
Facteur paramétrable: darken_color_factor(color, 0.35)
*/
/* Assombrit une couleur (divise par 2) pour les côtés */
int	darken_color(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r /= 2;
	g /= 2;
	b /= 2;
	return ((r << 16) | (g << 8) | b);
}
