/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:52:00 by eieong            #+#    #+#             */
/*   Updated: 2025/11/03 17:29:30 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_pressed(int key, t_game *game)
{
	if (key == 65307)
		clean_game(game, 0);
	else
		printf("key pressed: %d\n", key);
	return (0);
}

void	mlx_launch(t_game *game)
{
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win_ptr, 17, StructureNotifyMask, clean_game, game);
	mlx_loop(game->mlx_ptr);
}

bool	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (false);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			1920, 1080, "Licorne 3D");
	if (!game->win_ptr)
		return (free(game->mlx_ptr), false);
	return (true);
}
