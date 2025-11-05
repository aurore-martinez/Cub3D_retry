/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:05:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 11:40:09 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*|	Step			|	Resultat							|
|-------------------|---------------------------------------|
|	Centrage (+0.5)	| Le joueur n’est pas colle au mur		|
|	Orientation		| `N/S/E/W` → dir + plan corrects		|
|	Plan cam		| FOV ≈ 66°, perpendiculaire à `dir`	|
|	Taille screen	| Fixe la resolution du rendu initial	|
*/

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

/* init la cam du joueur depuis sa position dans la map = t_game */
bool	init_player_from_game(t_data *data)
{
	int	row;
	int	col;

	if (!data || !data->game)
		return (false);
	row = data->game->player.y;
	col = data->game->player.x;

	/* position reelle = centre de la case de depart = spawn */
	data->player.pos.x = (double)row + 0.5;
	data->player.pos.y = (double)col + 0.5;

	set_dir_plane_from_char(&data->player, (char)data->game->player_char);

	/* taille fenerte ? res ??? */
	if (data->scr_w <= 0)
		data->scr_w = SCR_W;
	if (data->scr_h <= 0)
		data->scr_h = SCR_H;
	return (true);
}
