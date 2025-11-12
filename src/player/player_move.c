/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/12 13:46:24 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	handle_ad_keys(int key, t_data *d, double move_speed, double margin)
{
	double	nx;
	double	ny;

	if (!d)
		return (false);
	if (key == KEY_A)
	{
		nx = d->player.pos.x - d->player.plane.x * move_speed;
		ny = d->player.pos.y - d->player.plane.y * move_speed;
		apply_walk(d, nx, ny, margin);
		return (true);
	}
	if (key == KEY_D)
	{
		nx = d->player.pos.x + d->player.plane.x * move_speed;
		ny = d->player.pos.y + d->player.plane.y * move_speed;
		apply_walk(d, nx, ny, margin);
		return (true);
	}
	return (false);
}

static bool	handle_ws_keys(int key, t_data *d, double move_speed, double margin)
{
	double	nx;
	double	ny;

	if (!d)
		return (false);
	if (key == KEY_W || key == KEY_UP)
	{
		nx = d->player.pos.x + d->player.dir.x * move_speed;
		ny = d->player.pos.y + d->player.dir.y * move_speed;
		apply_walk(d, nx, ny, margin);
		return (true);
	}
	if (key == KEY_S || key == KEY_DOWN)
	{
		nx = d->player.pos.x - d->player.dir.x * move_speed;
		ny = d->player.pos.y - d->player.dir.y * move_speed;
		apply_walk(d, nx, ny, margin);
		return (true);
	}
	return (false);
}

static bool	handle_turn_keys(int key, t_data *d, double rot_speed)
{
	if (!d)
		return (false);
	if (key == KEY_LEFT)
	{
		turn_player(d, rot_speed);
		return (true);
	}
	if (key == KEY_RIGHT)
	{
		turn_player(d, -rot_speed);
		return (true);
	}
	return (false);
}

void	handle_player_moves(int key, t_data *d)
{
	double	move_speed;
	double	rot_speed;
	double	margin;

	if (!d)
		return ;
	move_speed = MOVE_SPEED;
	rot_speed = ROT_SPEED;
	margin = 0.2; // a 0.2 cell du mur suffit ??
	if (handle_ws_keys(key, d, move_speed, margin))
		return ;
	if (handle_ad_keys(key, d, move_speed, margin))
		return ;
	if (handle_turn_keys(key, d, rot_speed))
		return ;
}
