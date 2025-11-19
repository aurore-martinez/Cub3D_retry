/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_focus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 14:50:54 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_focus_player(t_data *d, int ts, t_pos crop, t_pos start)
{
	int		radius;
	double	fx;
	double	fy;
	t_pos	center;

	if (!d)
		return ;
	fx = d->player.pos.y - start.y;
	fy = d->player.pos.x - start.x;
	center = (t_pos){
		crop.x + (int)(fx * ts + 0.5),
		crop.y + (int)(fy * ts + 0.5)
	};
	radius = ts / 3;
	if (radius < 1)
		radius = 1;
	draw_player_disc(&d->gfx->frame, center, radius, UI_PLAYER_COLOR);
}

static t_mview	mf_build_view(t_data *d, int radius)
{
	t_mview	v;
	int		pr;
	int		pc;

	v.ts = mf_tile_size(d);
	pr = (int)d->player.pos.x;
	pc = (int)d->player.pos.y;
	v.start.x = pr - radius;
	if (v.start.x < 0)
		v.start.x = 0;
	v.end.x = pr + radius;
	if (v.end.x >= d->game->height)
		v.end.x = d->game->height - 1;
	v.start.y = pc - radius;
	if (v.start.y < 0)
		v.start.y = 0;
	v.end.y = pc + radius;
	if (v.end.y >= d->game->width)
		v.end.y = d->game->width - 1;
	v.crop.x = 20;
	v.crop.y = 20;
	return (v);
}

static void	mf_draw_cells(t_data *d, t_mview v)
{
	int		row;
	int		col;
	char	c;
	t_point	cell;
	t_point	off;

	off.x = v.crop.x - v.start.y * v.ts;
	off.y = v.crop.y - v.start.x * v.ts;
	row = v.start.x;
	while (row <= v.end.x)
	{
		col = v.start.y;
		while (col <= v.end.y)
		{
			c = d->game->map[row][col];
			if (c != ' ')
			{
				cell = (t_point){off.x + col * v.ts, off.y + row * v.ts,
					mm_color_for_cell(d, c)};
				draw_minimap_cell(&d->gfx->frame, cell, v.ts);
			}
			col++;
		}
		row++;
	}
}

void	draw_minimap_focus(t_data *d)
{
	t_mview	v;
	int		r;

	if (!d || !d->game || !d->game->map)
		return ;
	r = 8;
	v = mf_build_view(d, r);
	mf_draw_cells(d, v);
	draw_focus_player(d, v.ts, v.crop, v.start);
	draw_minimap_fov(d);
}

/* Changer start_col/row = crop.
Changer tile_size = zoom.
Changer offset_x/y = pan (position fixe coin sup gauche). */

/* c = pos pl en px sur la minimap (centre), apres mise a l echelle (ts)
et decalage (crop)*/

/*
** Dessine le joueur sur la minimap focus comme un disque rempli.
**
** Paramètres:
** - d     : contexte (frame buffer, position du joueur).
** - ts    : taille d'une tuile (pixels) sur la minimap focus.
** - crop  : décalage en pixels du coin haut-gauche de la minimap dans
** la fenêtre.
** - start : cellule (ligne/colonne) du coin haut-gauche de la fenêtre
** de carte affichée.
**
** Etapes:
** 1) Calcule l'offset du joueur par rapport à 'start' (en tuiles), puis
** convertit en pixels et décale par 'crop' pour obtenir le centre du disque.
** 2) Rayon r = max(1, ts/3).
** 3) Parcourt un carré centré et remplit le disque via px^2 + py^2 <= r^2.
**
** Couleur: UI_PLAYER_COLOR. Complexité: O(r^2).
*/
