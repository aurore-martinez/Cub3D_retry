/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:05:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/06 13:38:44 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* “player” {0} */
static void	zero_player(t_vec *p)
{
	p->pos.x = 0.0;
	p->pos.y = 0.0;
	p->dir.x = 0.0;
	p->dir.y = 0.0;
	p->plane.x = 0.0;
	p->plane.y = 0.0;
}

/* init data */
bool	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("Error");
		return (false);
	}
	ft_memset(*data, 0, sizeof(t_data));
	(*data)->game = NULL;
	(*data)->scr_w = SCR_W;
	(*data)->scr_h = SCR_H;
	zero_player(&(*data)->player);
	return (true);
}

/* oriente la direction et le plan cam selon le spawn */
static void	set_dir_plane_from_char(t_vec *player, char c)
{
	if (c == 'N')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else if (c == 'S')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	else if (c == 'E')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else if (c == 'W')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
}

/* init la cam du joueur depuis sa position dans la map = t_game
position reelle = +0.5 centre de la case de depart = spawn */
bool	init_player_from_game(t_data *data)
{
	int	row;
	int	col;

	if (!data || !data->game)
		return (false);
	row = data->game->player.y;
	col = data->game->player.x;
	data->player.pos.x = (double)row + 0.5;
	data->player.pos.y = (double)col + 0.5;
	set_dir_plane_from_char(&data->player, (char)data->game->player_char);

	/* taille fenerte ? res ??? */
	if (data->scr_w <= 0)
		data->scr_w = 960;
	if (data->scr_h <= 0)
		data->scr_h = 640;
	return (true);
}
