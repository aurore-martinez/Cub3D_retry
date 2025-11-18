/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/18 14:44:31 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_input_vector(t_data *d, double *forward, double *side)
{
	if (d->key.w || d->key.up)
		*forward += 1.0;
	if (d->key.s || d->key.down)
		*forward -= 1.0;
	if (d->key.d)
		*side += 1.0;
	if (d->key.a)
		*side -= 1.0;
}

/* garde la meme vitesse sur les deplacements diagonaux */
static void	diagonal_move(double *forward, double *side)
{
	double	len;

	len = sqrt((*forward) * (*forward) + (*side) * (*side));
	if (len > 1.0)
	{
		*forward /= len;
		*side /= len;
	}
}

static bool	apply_move(t_data *d, double forward, double side, double margin)
{
	double	nx;
	double	ny;

	if (forward != 0.0 || side != 0.0)
	{
		nx = d->player.pos.x + (d->player.dir.x * forward
				+ d->player.plane.x * side) * MOVE_SPEED;
		ny = d->player.pos.y + (d->player.dir.y * forward
				+ d->player.plane.y * side) * MOVE_SPEED;
		apply_walk(d, nx, ny, margin);
		return (true);
	}
	return (false);
}

static bool	rotation_move(t_data *d, double rot_speed)
{
	if (d->key.left)
	{
		turn_player(d, rot_speed);
		return (true);
	}
	if (d->key.right)
	{
		turn_player(d, -rot_speed);
		return (true);
	}
	return (false);
}

bool	handle_player_moves(t_data *d)
{
	double	margin;
	double	forward;
	double	side;
	bool	moved;

	if (!d)
		return (false);
	margin = 0.2;
	forward = 0.0;
	side = 0.0;
	moved = false;
	get_input_vector(d, &forward, &side);
	diagonal_move(&forward, &side);
	if (apply_move(d, forward, side, margin))
		moved = true;
	if (rotation_move(d, ROT_SPEED))
		moved = true;
	return (moved);
}
