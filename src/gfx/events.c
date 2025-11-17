/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:30 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/17 17:57:53 by eieong           ###   ########.fr       */
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

int	on_key_press(int key, t_data *d)
{
	if (key == KEY_M && d && d->gfx)
	{
		d->gfx->cam.show_full_minimap = !d->gfx->cam.show_full_minimap;
		request_redraw(d);
		return (0);
	}
	else if (key == KEY_ESC)
		on_destroy_event(d);
	else if (key == KEY_W)
		d->key.w = true;
	else if (key == KEY_A)
		d->key.a = true;
	else if (key == KEY_S)
		d->key.s = true;
	else if (key == KEY_D)
		d->key.d = true;
	else if (key == KEY_UP)
		d->key.up = true;
	else if (key == KEY_DOWN)
		d->key.down = true;
	else if (key == KEY_LEFT)
		d->key.left = true;
	else if (key == KEY_RIGHT)
		d->key.right = true;
	return (0);
}

int	on_key_release(int key, t_data *d)
{
	if (key == KEY_W)
		d->key.w = false;
	else if (key == KEY_A)
		d->key.a = false;
	else if (key == KEY_S)
		d->key.s = false;
	else if (key == KEY_D)
		d->key.d = false;
	else if (key == KEY_UP)
		d->key.up = false;
	else if (key == KEY_DOWN)
		d->key.down = false;
	else if (key == KEY_LEFT)
		d->key.left = false;
	else if (key == KEY_RIGHT)
		d->key.right = false;
	return (0);
}

int	on_mouse(int x, int y, t_data *d)
{
	int	center_x;
	int	center_y;
	int	dx;
	const double	angle = 0.0015; // radians per pixel

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
	if (handle_player_moves(d))
		request_redraw(d);
	if (d->need_redraw)
	{
		render_frame(d);
		d->need_redraw = false;
	}
	return (0);
}
