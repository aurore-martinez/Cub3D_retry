/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_focus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 11:32:15 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Changer start_col/row = crop.
Changer tile_size = zoom.
Changer offset_x/y = pan (position fixe coin sup gauche). */

/* ================= Minimap Focus helpers ================= */
/* Taille d'une tuile en mode focus (base_ts * zoom), clampée à >= 1 */
int	mf_tile_size(t_data *d)
{
	int		base_ts;
	double	zoom;
	int		ts;

	if (!d)
		return (1);
	base_ts = mm_tile_size(d);
	zoom = mf_get_zoom_factor(d, 8, base_ts);
	ts = (int)(base_ts * zoom);
	if (ts <= 0)
		ts = 1;
	return (ts);
}

/* Décalage X (pixels) du coin haut-gauche du viewport focus */
int	mf_off_x(t_data *d)
{
	int ts;
	int r;
	int p_col;
	int start_col;

	if (!d || !d->game)
		return (20);
	ts = mf_tile_size(d);
	r = 8;
	p_col = (int)d->player.pos.y;
	start_col = p_col - r;
	if (start_col < 0)
		start_col = 0;
	/* Même logique de bord que le dessin: fenêtre peut se réduire près des bords */
	return (20 - start_col * ts);
}

/* Décalage Y (pixels) du coin haut-gauche du viewport focus */
int	mf_off_y(t_data *d)
{
	int ts;
	int r;
	int p_row;
	int start_row;

	if (!d || !d->game)
		return (20);
	ts = mf_tile_size(d);
	r = 8;
	p_row = (int)d->player.pos.x;
	start_row = p_row - r;
	if (start_row < 0)
		start_row = 0;
	return (20 - start_row * ts);
}

static int	mf_color_for_cell(t_data *d, char c)
{
	if (c == '1')
		return (DARKGRAY);
	if (c == '0')
		return (BEIGE);
	if (c == ' ')
		return (BLACK);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (d->game->elements.rgb_floor);
	return (GRAY);
}

/* static void	draw_focus_cell(t_data *d, int x, int y, int size, int color) */
/* cell (x,y,color) -> dessine une cell size x size */
static void	draw_focus_cell(t_data *d, t_point cell, int size)
{
	int		j;
	int		i;
	t_point	p;

	if (!d || size <= 0)
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
			draw_pixel(&d->gfx->frame, p);
			i++;
		}
		j++;
	}
}

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
	int		pr;
	int		px;
	int		py;
	t_pos	c;
	double	fx;
	double	fy;
	t_point	p;

	if (!d)
		return ;
	fx = d->player.pos.y - start.y;
	fy = d->player.pos.x - start.x;
	c = (t_pos){crop.x + (int)(fx * ts + 0.5), crop.y + (int)(fy * ts + 0.5)};
	pr = ts / 3;
	if (pr < 1)
		pr = 1;
	py = -pr;
	while (py <= pr)
	{
		px = -pr;
		while (px <= pr)
		{
			if (px * px + py * py <= pr * pr)
			{
				p.x = c.x + px;
				p.y = c.y + py;
				p.color = UI_PLAYER_COLOR;;
				draw_pixel(&d->gfx->frame, p);
			}
			px++;
		}
		py++;
	}
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
				draw_focus_cell(
					d,
					(t_point){
						crop.x + (col - start.y) * ts,
						crop.y + (row - start.x) * ts,
						mf_color_for_cell(d, d->game->map[row][col])
					},
					ts
				);
			col++;
		}
		row++;
	}
	draw_focus_player(d, ts, crop, start);
	draw_minimap_fov(d);
}
