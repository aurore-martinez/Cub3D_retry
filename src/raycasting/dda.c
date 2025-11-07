/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:41:07 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/06 13:58:44 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* cameraX en [-1,1] :	-1 = left	0 = centre	 +1 = right */
void	ray_build_dir(const t_vec *pl, double cameraX, t_dda *r)
{
	r->ray_row = pl->dir.x + pl->plane.x * cameraX;
	r->ray_col = pl->dir.y + pl->plane.y * cameraX;
}


/* init DDA pour (r->rayRow, r->rayCol) */
void	dda_init(const t_vec *pl, t_dda *r)
{
	r->cell_row = (int)pl->pos.x;
	r->cell_col = (int)pl->pos.y;
	if (r->ray_row == 0.0)
		r->delta_row = BIG;
	else
		r->delta_row = fabs(1.0 / r->ray_row);
	if (r->ray_col == 0.0)
		r->delta_col = BIG;
	else
		r->delta_col = fabs(1.0 / r->ray_col);
	if (r->ray_row < 0.0)
	{
		r->step_row = -1;
		r->side_dist_row = (pl->pos.x - r->cell_row) * r->delta_row;
	}
	else
	{
		r->step_row = 1;
		r->side_dist_row = (r->cell_row + 1.0 - pl->pos.x) * r->delta_row;
	}
	if (r->ray_col < 0.0)
	{
		r->step_col = -1;
		r->side_dist_col = (pl->pos.y - r->cell_col) * r->delta_col;
	}
	else
	{
		r->step_col = 1;
		r->side_dist_col = (r->cell_col + 1.0 - pl->pos.y) * r->delta_col;
	}
}

/* boucle DDA : avance jusuq'a hit == false */
bool	dda_advance_until_hit(t_game *g, t_dda *r)
{
	bool	hit;

	if (!g || !r)
		return (false);
	hit = false;
	while (hit == false)
	{
		if (r->side_dist_row < r->side_dist_col)
		{
			r->side_dist_row += r->delta_row;
			r->cell_row += r->step_row;
			r->side_hit_col = false;
		}
		else
		{
			r->side_dist_col += r->delta_col;
			r->cell_col += r->step_col;
			r->side_hit_col = true;
		}
		if (is_wall(g, r->cell_row, r->cell_col) == true)
			hit = true;
	}
	return (hit);
}

/* distance perpendiculaire depuis etat DDA et le side_hit */
double	dda_perp_distance(t_dda *r)
{
	double	perp;

	if (r->side_hit_col == false)
		perp = r->side_dist_row - r->delta_row;
	else
		perp = r->side_dist_col - r->delta_col;
	if (perp <= 0.0)
		perp = 0.0001;
	return (perp);
}

/*
                         ^ dir = (-1, 0)
                         |
        plane (-0.66, 0) | (0.66, 0)point
                         |
   rayon gauche   \   |   /   rayon droit
                   \  |  /
                    \ | /
                      P  ← pos.x = 2.5, pos.y = 2.5

*/

/* form Benoit :
pour tous x (o, scr_w -1) : indice de la colonne dessiner

player.pos.x = row (ligne dans la map)
player.pos.y = col (colonne dans la map)

posX posY -> data.player.pos.x / y
dirX dirY -> data.player.dir.x / y
planeX planeY -> data.player.plane.x / y


calcul dy rayon pour la col x
camX = 2 x (x / scr_w) - 1
ray_dirX = dirX + planeX x camX
ray_dirY = dirY + planeY x camY

position dans la grille
gameX = posX -> game.player.x
gameY = posY -> game.player.y

distances initiales
dist_x = (1/ray_dirX)
dist_y = (1/ray_dirX)
*/

/* cameraX   = 2.0 * x / scr_w - 1.0;

Direction du rayon projetée dans l’espace monde (row/col)
rayRow    = player.dir.x   + player.plane.x   * cameraX;
rayCol    = player.dir.y   + player.plane.y   * cameraX;

Case de départ dans la grille
cellRow   = (int) player.pos.x;
cellCol   = (int) player.pos.y;

Distances “delta” (coût pour franchir une case dans chaque axe)
deltaRow  = (rayRow == 0.0) ? BIG : fabs(1.0 / rayRow);
deltaCol  = (rayCol == 0.0) ? BIG : fabs(1.0 / rayCol);

Choix des steps et distances initiales “sideDist”
if (rayRow < 0)
{
	stepRow = -1;
	sideDistRow = (player.pos.x - cellRow) * deltaRow;
} else {
	stepRow =  1;
	sideDistRow = (cellRow + 1.0 - player.pos.x) * deltaRow;
}
if (rayCol < 0)
{
	stepCol = -1;
	sideDistCol = (player.pos.y - cellCol) * deltaCol;
} else {
	stepCol =  1;
	sideDistCol = (cellCol + 1.0 - player.pos.y) * deltaCol;
}
 */

/* hit = 0;
while (hit == 0)
{
		if (sideDistRow < sideDistCol)
		{
			sideDistRow += deltaRow;
			cellRow += stepRow;
			side = 0; // on a franchi une frontière “row” (verticale en terme de mur)
		} else {
			sideDistCol += deltaCol;
			cellCol += stepCol;
			side = 1; // frontière “col”
		}
		if (is_wall_cell(game, cellRow, cellCol))
		{
			hit = 1;
		}
}
*/


