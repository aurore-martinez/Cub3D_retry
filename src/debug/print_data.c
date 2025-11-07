/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:56:44 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/07 09:28:00 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_player_data(t_data *d)
{
	double	px;
	double	py;
	double	dirX;
	double	dirY;
	double	plX;
	double	plY;

	if (!d)
		return ;
	px = d->player.pos.x;
	py = d->player.pos.y;
	dirX = d->player.dir.x;
	dirY = d->player.dir.y;
	plX = d->player.plane.x;
	plY = d->player.plane.y;
	printf("=== player from d ===\n");
	printf("pos   : x = %.2f | y = %.2f\n", px, py);
	printf("dir   : x = %.2f | y = %.2f\n", dirX, dirY);
	printf("plane : x = %.2f | y = %.2f\n", plX, plY);
	printf("spawn : row = %d | col = %d | char = %c\n",
		d->game->player.y, d->game->player.x, (char)d->game->player_char);
	printf("scr   : %dx%d\n", d->scr_w, d->scr_h);
	printf("===\n");
}

void	print_dda(t_dda *r)
{
	int	side_hit;

	if (!r)
		return ;
	printf("=== t_dda ===\n");
	printf("ray_row=%.6f\n", r->ray_row);
	printf("ray_col=%.6f\n", r->ray_col);
	printf("cell_row=%d\n", r->cell_row);
	printf("cell_col=%d\n", r->cell_col);
	printf("side_dist_row=%.6f\n", r->side_dist_row);
	printf("side_dist_col=%.6f\n", r->side_dist_col);
	printf("delta_row=%.6f\n", r->delta_row);
	printf("delta_col=%.6f\n", r->delta_col);
	printf("step_row=%d\n", r->step_row);
	printf("step_col=%d\n", r->step_col);
	{
		if (r->side_hit_col)
			side_hit = 1;
		else
			side_hit = 0;
		printf(" side_hit_col=%d\n", side_hit);
	}
}
