/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:45:57 by eieong            #+#    #+#             */
/*   Updated: 2025/11/12 13:46:43 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	can_move_to(t_game *g, double nx, double ny, double margin)
{
	int	r0;
	int	c0;
	int	r1;
	int	c1;
	int	c;

	if (!g || !g->map)
		return (false);
	r0 = (int)floor(nx - margin);
	c0 = (int)floor(ny - margin);
	r1 = (int)floor(nx + margin);
	c1 = (int)floor(ny + margin);
	while (r0 <= r1)
	{
		c = c0;
		while (c <= c1)
		{
			if (is_wall(g, r0, c))
				return (false);
			c++;
		}
		r0++;
	}
	return (true);
}

void	apply_walk(t_data *d, double nx, double ny, double margin)
{
	if (!d)
		return ;
	if (can_move_to(d->game, nx, d->player.pos.y, margin))
		d->player.pos.x = nx;
	if (can_move_to(d->game, d->player.pos.x, ny, margin))
		d->player.pos.y = ny;
}

void	turn_player(t_data *d, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!d)
		return ;
	old_dir_x = d->player.dir.x;
	old_plane_x = d->player.plane.x;
	d->player.dir.x = d->player.dir.x * cos(angle)
		- d->player.dir.y * sin(angle);
	d->player.dir.y = old_dir_x * sin(angle) + d->player.dir.y * cos(angle);
	d->player.plane.x = d->player.plane.x * cos(angle)
		- d->player.plane.y * sin(angle);
	d->player.plane.y = old_plane_x * sin(angle)
		+ d->player.plane.y * cos(angle);
}
