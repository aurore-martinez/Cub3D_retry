/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:56:44 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 11:30:50 by eieong           ###   ########.fr       */
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

void	print_map(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			printf("%c|", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	print_game(t_game *g)
{
	if (!g)
	{
		printf("[DEBUG] game pointer NULL\n");
		return ;
	}
	printf("=== t_game ===\n");
	printf("map size: %d x %d\n", g->height, g->width);
	printf("player pos: x=%d | y=%d\n", g->player.x, g->player.y);
	printf("player dir: %c\n", (char)g->player_char);
	printf("fd : %d\n", g->fd);
	printf("textures :\n");
	printf("N : %s\n", g->elements.path_north);
	printf("S: %s\n", g->elements.path_south);
	printf("W: %s\n", g->elements.path_west);
	printf("E: %s\n", g->elements.path_east);
	printf("===\n");
}
