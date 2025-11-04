/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:56:44 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 08:38:53 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_player_data(t_data *d)
{
	printf("=== player ===\n");
	printf("pos   : x=%.2f y=%.2f\n", d->player.pos.x, d->player.pos.y);
	printf("dir   : x=%.2f y=%.2f\n", d->player.dir.x,  d->player.dir.y);
	printf("plane : x=%.2f y=%.2f\n", d->player.plane.x,d->player.plane.y);
	printf("depart = spawn : row=%d col=%d char=%c\n",
		d->game->player.y, d->game->player.x, (char)d->game->player_char);
	printf("scr   : %dx%d\n", d->scr_w, d->scr_h);
	printf("===\n");
}

