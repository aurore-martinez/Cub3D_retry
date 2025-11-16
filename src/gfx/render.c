/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:14:56 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/16 16:01:37 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int render_frame(t_data *d)
{
	if (!d || !d->gfx)
		return (0);
	render_walls(d);
	draw_crosshair(d);
	if (d->gfx && d->gfx->cam.show_full_minimap)
		draw_minimap_focus(d);
	else
		draw_minimap(d);
	mlx_put_image_to_window(d->gfx->mlx, d->gfx->win, d->gfx->frame.img, 0, 0);
	printf("APPEL RENDER FRAME ");
	return (0);
}

/* Helper chat pour debug :
use :
env CUB3D_DEBUG=<valeur> timeout <time> ./cub3D <chemin_map>

<valeur> :
center → affiche le debug uniquement pour la colonne centrale
all → affiche pour toutes les colonnes (très verbeux)
<num> → un indice de col précis, ex. 320
vide / unset → aucun debug

ex :
env CUB3D_DEBUG=center timeout 2s ./cub3D assets/maps_chat/map_corner.cub
*/

static void	help_env_print_ray_debug(t_data *d, int x)
{
	char	*dbg;
	int		col;

	if (!d)
		return ;
	dbg = getenv("CUB3D_DEBUG");
	if (!dbg)
		return ;
	if (ft_strcmp(dbg, "all") == 0)
	{
		print_ray_debug(d, x);
		return ;
	}
	if (ft_strcmp(dbg, "center") == 0)
	{
		if (x == d->scr_w / 2)
			print_ray_debug(d, x);
		return ;
	}
	col = ft_atoi(dbg);
	if (col == x)
		print_ray_debug(d, x);
}

void render_walls(t_data *d)
{
	int		x;
	double	cameraX;
	double	perp;
	int		side;
	int		hit_r;
	int		hit_c;
	int		line_h;
	int		top;
	int		bot;
	int		wall;

	x = 0;
	while (x < d->scr_w)
	{
		cameraX = 2.0 * x / (double)d->scr_w - 1.0;

		if (!cast_ray_perp_dist(d, cameraX, &perp, &side, &hit_r, &hit_c))
		{
			x++;
			continue ;
		}

		/* conditional debug printing — a sup */
		help_env_print_ray_debug(d, x);
		if (perp < 1e-6)
			perp = 1e-6;

		line_h = (int)(d->scr_h / perp);
		top = -line_h / 2 + d->scr_h / 2;
		bot = line_h / 2 + d->scr_h / 2;
		if (top < 0)
			top = 0;
		if (bot >= d->scr_h)
			bot = d->scr_h - 1;

		if (side == 1)
			wall = WALL_MAIN;
		else
			wall = WALL_SHADOW;

		// plafond
		if (top > 0)
			draw_col(d, x, 0, top - 1, d->game->elements.rgb_ceiling);

		/* conditional debug printing — a sup */
		help_env_print_ray_debug(d, x);

		// mur
		draw_col(d, x, top, bot, wall);

		// sol
		if (bot + 1 < d->scr_h)
			draw_col(d, x, bot + 1, d->scr_h - 1, d->game->elements.rgb_floor);

		x++;
	}
}

