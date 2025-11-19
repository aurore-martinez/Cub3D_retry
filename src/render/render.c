/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:14:56 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 16:01:29 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
Draw frame complet puis pousser l'image à la fenetre.
Étapes:
1. Vérifie la validité de d et de d->gfx.
2. Appelle render_walls: lance le raycasting colonne par colonne.
3. Dessine un réticule (draw_crosshair) si présent.
4. Affiche soit la minimap complète soit la minimap focus selon
le flag show_full_minimap.
5. Transfère le buffer image vers la fenêtre (mlx_put_image_to_window).
6. printf debug (peut être retiré pour éviter le spam).

DEBUG : apel et callback 	printf("APPEL RENDER FRAME ");
TODO : Retour: 0 ? passer en bool ?
*/

int	render_frame(t_data *d)
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
	return (0);
}

/*
Draw la portion mur pour une colonne (x) avec la texture
Étapes:
1. select_texture() selon le côté touché (side) → params.texture.
2. get_wall_x() : position de collision fractionnelle sur la face → [0;1).
3. get_texture_x() : index horizontal dans la texture (flip si orientation).
4. Calcule orig_line_h/top/bot (hauteur théorique non clampée).
5. Si clamp top > orig_top → calcule tex_offset pour commencer
plus bas dans la texture.
6. Prépare t_tex_params (line_h clampée, offset vertical,
side pour shading éventuel).
7. draw_textured_col(): copie pixels texture → frame.
Fallback:
- Si texture introuvable → colonne magenta (debug).

Notes :
- TEX_SIZE use pour mapping vertical (suppose textures 256x256).
- perp distance secure avant appel
*/
static void	render_tex_wall(t_data *d, t_dda *ray, t_render *s)
{
	t_tex_params	p;
	double			wall_x;
	int				orig_top;
	int				tex_off;

	p.texture = select_texture(d, ray, s->side);
	if (!p.texture)
	{
		draw_col(d, (t_pos){s->x, s->top}, s->bot, 0xFF00FF);
		return ;
	}
	wall_x = get_wall_x(d, ray, s->perp, s->side);
	p.tex_x = get_texture_x(ray, wall_x, s->side);
	orig_top = -s->line_h / 2 + d->scr_h / 2;
	if (s->top > orig_top)
		tex_off = (int)(((double)(s->top - orig_top) * TEX_SIZE)
				/ (double)s->line_h);
	else
		tex_off = 0;
	p.line_h = s->bot - s->top + 1;
	p.orig_line_h = s->line_h;
	p.tex_y_offset = tex_off;
	p.side = s->side;
	draw_textured_col(d, s, &p);
}

/*
Remplis s (t_render) avec distances, bornes verticales clampées et side.
*/
static void	fill_t_render(t_data *d, t_dda *ray, t_render *s)
{
	s->perp = dda_perp_distance(ray);
	if (s->perp < 1e-6)
		s->perp = 1e-6;
	s->line_h = (int)(d->scr_h / s->perp);
	s->top = -s->line_h / 2 + d->scr_h / 2;
	s->bot = s->line_h / 2 + d->scr_h / 2;
	if (s->top < 0)
		s->top = 0;
	if (s->bot >= d->scr_h)
		s->bot = d->scr_h - 1;
	if (ray->side_hit_col)
		s->side = 0;
	else
		s->side = 1;
}

/*
Calcule et dessine plafond/mur/sol d’une colonne écran.
*/
static void	render_column(t_data *d, int x)
{
	t_dda		ray;
	t_render	s;
	double		camera_x;

	camera_x = 2.0 * x / (double)d->scr_w - 1.0;
	ray_build_dir(&d->player, camera_x, &ray);
	dda_init(&d->player, &ray);
	if (!dda_advance_until_hit(d->game, &ray))
		return ;
	fill_t_render(d, &ray, &s);
	s.x = x;
	if (s.top > 0)
		draw_col(d, (t_pos){x, 0}, s.top - 1, d->game->elements.rgb_ceiling);
	render_tex_wall(d, &ray, &s);
	if (s.bot + 1 < d->scr_h)
		draw_col(d, (t_pos){x, s.bot + 1}, d->scr_h - 1,
			d->game->elements.rgb_floor);
}

/*
Boucle écran: lance render_column() pour chaque x.
*/
void	render_walls(t_data *d)
{
	int	x;

	x = 0;
	while (x < d->scr_w)
	{
		render_column(d, x);
		x++;
	}
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

/* static void	help_env_print_ray_debug(t_data *d, int x)
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
} */
