/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:05:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/03 19:06:41 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*| Étape           | Résultat                              |
| --------------- | ------------------------------------- |
| Centrage (+0.5) | Le joueur n’est pas colle au mur      |
| Orientation     | `N/S/E/W` → dir + plan corrects |
| Plan caméra     | FOV ≈ 66°, perpendiculaire à `dir`    |
| Taille écran    | Fixe la résolution du rendu initial   |
*/

/* oriente la direction et le plan cam selon le spawn */
void	set_dir_plane_from_char(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player.dir.x = -1;
		data->player.dir.y = 0;
		data->player.plane.x = 0;
		data->player.plane.y = 0.66;
	}
	else if (c == 'S')
	{
		data->player.dir.x = 1;
		data->player.dir.y = 0;
		data->player.plane.x = 0;
		data->player.plane.y = -0.66;
	}
	else if (c == 'E')
	{
		data->player.dir.x = 0;
		data->player.dir.y = 1;
		data->player.plane.x = 0.66;
		data->player.plane.y = 0;
	}
	else if (c == 'W')
	{
		data->player.dir.x = 0;
		data->player.dir.y = -1;
		data->player.plane.x = -0.66;
		data->player.plane.y = 0;
	}
}

/* initialise la cam du joueur depuis sa position dans la map = game */
void	init_player_from_game(t_data *data)
{
	// indices de case parsing
	int	row = data->game.player.y;
	int	col = data->game.player.x;

	// position reelle = centre de la case de spawn
	data->player.pos.x = (double)row + 0.5;
	data->player.pos.y = (double)col + 0.5;

	set_dir_plane_from_char(data, (char)data->game.player_char);

	// taille de la fenetre ??
	data->scr_w = 960;
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
	printf("spawn : row = %d | col = %d | char = %c\n",
		data->game.player.y, data->game.player.x, (char)data->game.player_char);
	printf("scr   : %dx%d\n", data->scr_w, data->scr_h);
	printf("===\n");
}
