/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:34:10 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 14:12:02 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* dessine une cell*/
static void	draw_minimap_cell(t_img *img, t_point cell, int size)
{
	int		i;
	int		j;
	t_point	p;

	if (!img || size <= 0)
		return ;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			p.x = cell.x + i;
			p.y = cell.y + j;
			p.color = cell.color;
			draw_pixel(img, p);
			i++;
		}
		j++;
	}
}

static void	draw_player_disc(t_img *img, t_pos center, int radius, int color)
{
	int		dy;
	int		dx;
	int		r2;
	t_point	p;

	if (!img || radius <= 0)
		return ;
	r2 = radius * radius;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= r2)
			{
				p = (t_point){center.x + dx, center.y + dy, color};
				draw_pixel(img, p);
			}
			dx++;
		}
		dy++;
	}
}

/* debug: print full minimap player computed positions
printf("FULL: ts=%d off=(%d,%d) p=(%.3f,%.3f) cx=%d cy=%d\n",
ts, mm_off_x(d), mm_off_y(d), d->player.pos.x, d->player.pos.y, cx, cy); */

/* r = ft_max(1, ts/3); // essayer avec ca plutot radius 1 pixel
quand tile tres petit

c => center : position pixel du centre (joueur).
rel => va de -radius a +radius (distance horiz/vert par rapport au centre). */

/* petit cercle rempli pour le joueur */
static void	draw_minimap_player(t_data *d)
{
	int		ts;
	int		radius;
	t_pos	center;

	ts = mm_tile_size(d);
	radius = ts / 3;
	if (radius < 1)
		radius = 1;
	center = (t_pos){
		mm_off_x(d) + (int)(d->player.pos.y * ts + 0.5),
		mm_off_y(d) + (int)(d->player.pos.x * ts + 0.5)
	};
	draw_player_disc(&d->gfx->frame, center, radius, UI_PLAYER_COLOR);
}

/* boucle de dessin des cellules */
static void	draw_cells(t_data *d, int ts, int off_x, int off_y)
{
	int		row;
	int		col;
	char	c;
	t_point	p;

	row = 0;
	while (row < d->game->height && d->game->map[row])
	{
		col = 0;
		while (col < d->game->width)
		{
			c = d->game->map[row][col];
			if (c != ' ')
			{
				p = (t_point){off_x + col * ts, off_y + row * ts,
					mm_color_for_cell(d, c)};
				draw_minimap_cell(&d->gfx->frame, p, ts);
			}
			col++;
		}
		row++;
	}
}

/* mini-map complète */
/*
x = col
y = row
*/
void	draw_minimap(t_data *d)
{
	int	ts;
	int	off_x;
	int	off_y;

	if (!d || !d->game || !d->game->map)
		return ;
	ts = mm_tile_size(d);
	off_x = mm_off_x(d);
	off_y = mm_off_y(d);
	draw_cells(d, ts, off_x, off_y);
	draw_minimap_player(d);
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

/* minimap focus - crop with dynamic zoom */
void	draw_minimap_focus(t_data *d)
{
	int		ts;
	int		r;
	int		p_row;
	int		p_col;
	t_pos	start;
	t_pos	end;
	t_pos	crop;
	int		row;
	int		col;
	int		base_ts;
	double	zoom;

	if (!d || !d->game || !d->game->map)
		return ;
	r = 8;
	base_ts = mm_tile_size(d);
	zoom = mf_get_zoom_factor(d, r, base_ts);
	ts = (int)(base_ts * zoom);
	if (ts <= 0)
		ts = 1;
	p_row = (int)d->player.pos.x;
	p_col = (int)d->player.pos.y;
	start.x = p_row - r;
	if (start.x < 0)
		start.x = 0;
	end.x = p_row + r;
	if (end.x >= d->game->height)
		end.x = d->game->height - 1;
	start.y = p_col - r;
	if (start.y < 0)
		start.y = 0;
	end.y = p_col + r;
	if (end.y >= d->game->width)
		end.y = d->game->width - 1;
	crop.x = 20;
	crop.y = 20;
	row = start.x;
	while (row <= end.x)
	{
		col = start.y;
		while (col <= end.y)
		{
			if (d->game->map[row][col] != ' ')
				draw_minimap_cell(&d->gfx->frame,
					(t_point){crop.x + (col - start.y) * ts,
					crop.y + (row - start.x) * ts,
					mm_color_for_cell(d, d->game->map[row][col])}, ts);
			col++;
		}
		row++;
	}
	draw_focus_player(d, ts, crop, start);
	draw_minimap_fov(d);
}

/* ligne horizontale jaune au centre de la mini-map */
/* static void	draw_minimap_horizon(t_data *d)
{
	int		ts;
	int		map_w;
	int		map_h;
	int		mid_y;
	int		x;
	t_point	p;

	ts = mm_tile_size(d);
	map_w = d->game->width * ts;
	map_h = d->game->height * ts;
	mid_y = mm_off_y(d) + map_h / 2;

	x = mm_off_x(d);
	while (x < mm_off_x(d) + map_w)
	{
		p.x = x;
		p.y = mid_y;
		p.z = 0;
		p.color = RGB(255, 220, 0);
		draw_pixel(&d->gfx->frame, p);
		x++;
	}
} */
