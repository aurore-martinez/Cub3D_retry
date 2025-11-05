/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:14:56 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 12:46:53 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	render_frame(t_data *d)
{
	t_point	a;
	t_point	b;
	int		midy;
	int		midx;

	if (d == NULL)
		return (0);

	clear_frame(&d->gfx->frame, d->scr_w, d->scr_h, RGB(12, 12, 12));

	midy = d->scr_h / 2;
	midx = d->scr_w / 2;

	/* horizontale blanche au milieu */
	a.x = 0;
	a.y = midy;
	a.z = 0;
	a.color = RGB(255, 255, 255);
	b.x = d->scr_w - 1;
	b.y = midy;
	b.z = 0;
	b.color = RGB(255, 255, 255);
	draw_line(&d->gfx->frame, a, b);

	/* verticale rouge au milieu */
	a.x = midx;
	a.y = 0;
	a.z = 0;
	a.color = RGB(255, 0, 0);
	b.x = midx;
	b.y = d->scr_h - 1;
	b.z = 0;
	b.color = RGB(255, 0, 0);
	draw_line(&d->gfx->frame, a, b);

	draw_minimap(d);
	
	mlx_put_image_to_window(d->gfx->mlx, d->gfx->win, d->gfx->frame.img, 0, 0);
	return (0);
}
