/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:56:44 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 09:25:52 by aumartin         ###   ########.fr       */
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
