/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:30 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/17 15:04:21 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	on_destroy_event(t_data *d)
{
	if (d == NULL)
		return (0);
	clean_data(d);
	exit(EXIT_SUCCESS);
	return (0);
}

/* void	clear_frame(t_img *img, int w, int h, int color)
{
	int		x;
	int		y;
	t_point	p;

	if (img == NULL)
		return ;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			p.x = x;
			p.y = y;
			p.z = 0;
			p.color = color;
			draw_pixel(img, p);
			x++;
		}
		y++;
	}
} */

int	on_key_press(int key, t_data *d)
{
	if (key == KEY_M && d && d->gfx)
	{
		d->gfx->cam.show_full_minimap = !d->gfx->cam.show_full_minimap;
		request_redraw(d);
		return (0);
	}
	if (key == KEY_ESC)
		on_destroy_event(d);
	handle_player_moves(key, d);
	request_redraw(d);
	return (0);
}

int	on_mouse(int x, int y, t_data *d)
{
	// static int	last_x = -1;
	// int		dx;
	// double	angle;

	// (void)y;
	// if (!d)
	// 	return (0);
	// if (last_x == -1)
	// {
	// 	last_x = x;
	// 	return (0);
	// }
	// dx = x - last_x;
	// last_x = x;
	// if (dx == 0)
	// 	return (0);
	// angle = (double)dx * 0.0035; /* radians per pixel */
	// turn_player(d, -angle);
	// request_redraw(d);
	// return (0);

	int	center_x;
	int	center_y;
	int	dx;
	const double	angle = 0.0035; // radians per pixel

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

void	request_redraw(t_data *d)
{
	if (!d)
		return ;
	d->need_redraw = true;
}

int	loop_hook(t_data *d)
{
	if (!d)
		return (0);
	if (d->need_redraw)
	{
		render_frame(d);
		d->need_redraw = false;
	}
	return (0);
}
