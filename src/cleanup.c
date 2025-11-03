/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:09:02 by eieong            #+#    #+#             */
/*   Updated: 2025/10/30 15:46:42 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	gnl_clear(t_game *game, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(game->fd);
	}
	free(line);
}

void	clean_game(t_game *game)
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
		ft_freetab(game->map);
	free(game);
}
