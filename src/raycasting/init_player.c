/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:05:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 08:39:47 by aumartin         ###   ########.fr       */
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
		player->dir.x = -1; player->dir.y = 0;
		player->playerane.x = 0; player->plane.y = 0.66;
	}
	else if (c == 'S')
	{
		player->dir.x = 1; player->dir.y = 0;
		player->plane.x = 0; player->plane.y = -0.66;
	}
	else if (c == 'E')
	{
		player->dir.x = 0; player->dir.y = 1;
		player->plane.x = 0.66; player->plane.y = 0;
	}
	else if (c == 'W')
	{
		player->dir.x = 0; player->dir.y = -1;
		player->plane.x = -0.66; player->plane.y = 0;
	}
}

/* init la cam du joueur depuis sa position dans la map = t_game */
void	init_player_from_game(t_data *data)
{
	int	row;
	int	col;

	if (!data || !data->game)
		return ;
	row = data->game->player.y;
	col = data->game->player.x;

	/* position reelle = centre de la case de depart = spawn */
	data->player.pos.x = (double)row + 0.5;
	data->player.pos.y = (double)col + 0.5;

	set_dir_plane_from_char(&data->player, (char)data->game->player_char);

	/* taille fenerte ? res ??? */
	if (data->scr_w <= 0)
		data->scr_w = 960;
	if (data->scr_h <= 0)
		data->scr_h = 640;
}

void	print_check(t_data *data)
{
	double	px;
	double	py;

	px = data->player.pos.x;
	py = data->player.pos.y;
	printf("=== player (from data) ===\n");
	printf("pos   : x = %.2f | y = %.2f\n", px, py);
	printf("dir   : x = %.2f | y = %.2f\n",
		data->player.dir.x, data->player.dir.y);
	printf("plane : x = %.2f | y = %.2f\n",
		data->player.plane.x, data->player.plane.y);
	printf("depart = spawn : row=%d col=%d char=%c\n",
		data->game->player.y, data->game->player.x, (char)data->game->player_char);
	printf("scr   : %dx%d\n", data->scr_w, data->scr_h);
	printf("===\n");
}
