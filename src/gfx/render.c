/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:14:56 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/17 12:56:04 by eieong           ###   ########.fr       */
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

static void	render_textured_wall(t_data *d, int x, int top, int bot,
	t_dda *ray, double perp, int side)
{
	t_tex_params	params;
	double			wall_x;
	int				orig_line_h;
	int				orig_top;
	int				orig_bot;
	int				tex_offset;

	params.texture = select_texture(d, ray, side);
	if (!params.texture)
	{
		draw_col(d, x, top, bot, 0xFF00FF);
		return ;
	}
	wall_x = get_wall_x(d, ray, perp, side);
	params.tex_x = get_texture_x(ray, wall_x, side);

	/* hauteur non clampée du mur (celle utilisée pour le mapping vertical) */
	orig_line_h = (int)(d->scr_h / perp);
	orig_top = -orig_line_h / 2 + d->scr_h / 2;
	orig_bot = orig_line_h / 2 + d->scr_h / 2;

	/* si le top a été tronqué à 0 (ou bot à scr_h-1), calculer l'offset dans la texture */
	if (top > orig_top)
		tex_offset = (int)(((double)(top - orig_top) * TEX_SIZE) / (double)orig_line_h);
	else
		tex_offset = 0;

	params.line_h = bot - top + 1; /* hauteur réelle dessinée (clampée) */
	params.orig_line_h = orig_line_h;
	params.tex_y_offset = tex_offset;
	params.side = side;
	draw_textured_col(d, x, top, bot, &params);
}

void render_walls(t_data *d)
{
	int		x;
	double	cameraX;
	double	perp;
	int		side;
	int		line_h;
	int		top;
	int		bot;
	t_dda	ray;

	x = 0;
	while (x < d->scr_w)
	{
		cameraX = 2.0 * x / (double)d->scr_w - 1.0;

		// Construire le rayon complet
		ray_build_dir(&d->player, cameraX, &ray);
		dda_init(&d->player, &ray);

		if (!dda_advance_until_hit(d->game, &ray))
		{
			x++;
			continue ;
		}

		perp = dda_perp_distance(&ray);
		side = ray.side_hit_col ? 0 : 1;

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

		// plafond
		if (top > 0)
			draw_col(d, x, 0, top - 1, d->game->elements.rgb_ceiling);

		/* conditional debug printing — a sup */
		help_env_print_ray_debug(d, x);

		// mur
		render_textured_wall(d, x, top, bot, &ray, perp, side);

		// sol
		if (bot + 1 < d->scr_h)
			draw_col(d, x, bot + 1, d->scr_h - 1, d->game->elements.rgb_floor);

		x++;
	}
}

