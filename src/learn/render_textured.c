/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:20:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/27 14:05:50 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* static void	render_textured_wall(t_data *d, int x, int top, int bot,
	t_dda *ray, double perp, int side)
{
	t_tex_params	params;
	double			wall_x;

	// 1. Choisir la bonne texture selon la direction
	params.texture = select_texture(d, ray, side);

	// 2. Calculer où le rayon touche le mur (0.0 à 1.0)
	wall_x = get_wall_x(d, ray, perp, side);

	// 3. Calculer la coordonnée X dans la texture
	params.tex_x = get_texture_x(ray, wall_x, side);

	// 4. Paramètres pour dessiner la colonne (textures fixes TEX_SIZE)
	params.line_h = bot - top + 1;
	params.side = side;

	// 5. Dessiner la colonne de texture
	draw_textured_col(d, x, top, bot, &params);
}

/*
 * EXEMPLE COMPLET de render_walls() avec textures :
 */

/* void render_walls_with_textures(t_data *d)
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
	t_dda	ray;  // On aura besoin de la structure complète pour les textures

	x = 0;
	while (x < d->scr_w)
	{
		cameraX = 2.0 * x / (double)d->scr_w - 1.0;

		// Construire le rayon et faire le DDA
		ray_build_dir(&d->player, cameraX, &ray);
		dda_init(&d->player, &ray);

		if (!dda_advance_until_hit(d->game, &ray))
		{
			x++;
			continue ;
		}

		perp = dda_perp_distance(&ray);
		side = ray.side_hit_col ? 0 : 1;

		if (perp < 1e-6)
			perp = 1e-6;

		line_h = (int)(d->scr_h / perp);
		top = -line_h / 2 + d->scr_h / 2;
		bot = line_h / 2 + d->scr_h / 2;
		if (top < 0)
			top = 0;
		if (bot >= d->scr_h)
			bot = d->scr_h - 1;

		// PLAFOND
		if (top > 0)
			draw_col(d, x, 0, top - 1, d->game->elements.rgb_ceiling);

		// MUR AVEC TEXTURE
		render_textured_wall(d, x, top, bot, &ray, perp, side);

		// SOL
		if (bot + 1 < d->scr_h)
			draw_col(d, x, bot + 1, d->scr_h - 1, d->game->elements.rgb_floor);

		x++;
	}
} */
