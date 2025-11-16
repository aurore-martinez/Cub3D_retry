/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:09:02 by eieong            #+#    #+#             */
/*   Updated: 2025/11/16 17:42:24 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	destroy_texture(t_gfx *gfx)
{
	if (gfx->texture.north)
		mlx_destroy_image(gfx->mlx, gfx->texture.north);
	if (gfx->texture.south)
		mlx_destroy_image(gfx->mlx, gfx->texture.south);
	if (gfx->texture.west)
		mlx_destroy_image(gfx->mlx, gfx->texture.west);
	if (gfx->texture.east)
		mlx_destroy_image(gfx->mlx, gfx->texture.east);
}

static void	clean_mlx(t_gfx *gfx)
{
	destroy_texture(gfx);
	if (gfx->win)
		mlx_destroy_window(gfx->mlx, gfx->win);
	if (gfx->mlx)
	{
		mlx_destroy_display(gfx->mlx);
		free(gfx->mlx);
	}
	free(gfx);
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

static void	clean_game(t_game *game)
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
	free(game);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->game)
		clean_game(data->game);
	/* free MLX, textures, buf… */
	if (data->gfx)
		clean_mlx(data->gfx);
	free(data);
}
