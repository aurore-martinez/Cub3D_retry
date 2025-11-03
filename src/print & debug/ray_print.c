/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:56:44 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/03 18:24:08 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_player(t_vec *p)
{
	if (!p)
	{
		printf("player is NULL\n");
		return ;
	}
	printf("=== player ===\n");
	printf("pos   : x = %.2f | y = %.2f\n", p->pos.x, p->pos.y);
	printf("dir   : x = %.2f | y = %.2f\n", p->dir.x, p->dir.y);
	printf("plane : x = %.2f | y = %.2f\n", p->plane.x, p->plane.y);
	printf("===\n");
}

