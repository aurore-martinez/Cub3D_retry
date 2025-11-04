/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:24:06 by eieong            #+#    #+#             */
/*   Updated: 2025/11/04 09:52:02 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
