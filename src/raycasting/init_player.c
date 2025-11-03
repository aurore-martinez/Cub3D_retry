/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:05:48 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/03 18:22:59 by aumartin         ###   ########.fr       */
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

#define PX (data->player.pos.x)
#define PY (data->player.pos.y)

/* oriente la direction et le plan caméra selon le spawn */
static void	set_dir_plane_from_char(t_data *data, char c)
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

/* initialise la caméra du joueur depuis sa position dans la map */
void	init_player_from_spawn(t_data *data)
{
	// indices de case trouvés par le parsing
	int	row = data->map.player.y; // ligne dans la map
	int	col = data->map.player.x; // colonne dans la map

	// position réelle = centre de la case de spawn
	PX = (double)row + 0.5;
	PY = (double)col + 0.5;

	set_dir_plane_from_char(data, (char)data->map.player_char);

	// taille de la fenetre ??
	data->scr_w = 960;
	data->scr_h = 640;
}
