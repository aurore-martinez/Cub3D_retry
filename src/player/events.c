/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:30 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/18 17:30:50 by eieong           ###   ########.fr       */
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

static void	change_key_flag(int key, t_data *d)
{
	if (key == KEY_W)
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
	change_key_flag(key, d);
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
