/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:29:38 by eieong            #+#    #+#             */
/*   Updated: 2025/11/18 17:30:36 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	on_mouse(int x, int y, t_data *d)
{
	int				center_x;
	int				center_y;
	int				dx;
	const double	angle = 0.0015;

	if (!d || !d->key.mouse)
		return (0);
	center_x = d->scr_w / 2;
	center_y = d->scr_h / 2;
	dx = x - center_x;
	if (x == center_x && y == center_y)
		return (0);
	turn_player(d, -((double)dx * angle));
	mlx_mouse_move(d->gfx->mlx, d->gfx->win, center_x, center_y);
	request_redraw(d);
	return (0);
}

int on_clic(int button, int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	if (button != 3)
		return (0);
	if (d->key.mouse)
		d->key.mouse = false;
	else if (!d->key.mouse)
	{
		d->key.mouse = true;
		mlx_mouse_move(d->gfx->mlx, d->gfx->win,
			d->scr_w / 2, d->scr_h / 2);
	}
	return (0);
}

