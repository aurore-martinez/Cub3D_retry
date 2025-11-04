/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:09:02 by eieong            #+#    #+#             */
/*   Updated: 2025/11/04 14:23:33 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	clean_mlx(t_game *game)
{
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	gnl_clear(t_game *game, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(game->fd);
	}
	free(line);
}

int	clean_game(t_game *game, int ret)
{
	if (game->fd != -1)
		close(game->fd);
	if (game->elements.path_north)
		free(game->elements.path_north);
	if (game->elements.path_south)
		free(game->elements.path_south);
	if (game->elements.path_west)
		free(game->elements.path_west);
	if (game->elements.path_east)
		free(game->elements.path_east);
	if (game->map)
		free_split(game->map);
	clean_mlx(game);
	free(game);
	exit(ret);
	return (ret);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	on_destroy_event(data);
	if (data->game)
		clean_game(data->game,0);
	/* free MLX, textures, buf… */

	free(data);
}
