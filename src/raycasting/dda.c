/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:41:07 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 16:36:52 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* dir du rayon */
void	ray_build_dir(const t_vec *pl, double cameraX, double *rayRow,
	double *rayCol)
{
	*rayRow = pl->dir.x + pl->plane.x * cameraX;
	*rayCol = pl->dir.y + pl->plane.y * cameraX;
}

/* init DDA pour (rayRow, rayCol) */
void	dda_init(
	const t_vec *pl,
	double rayRow, double rayCol,
	int *cellRow, int *cellCol,
	double *deltaRow, double *deltaCol,
	int *stepRow, int *stepCol,
	double *sideDistRow, double *sideDistCol)
{
	*cellRow = (int)pl->pos.x;
	*cellCol = (int)pl->pos.y;
	if (rayRow == 0.0)
		*deltaRow = BIG;
	else
		*deltaRow = fabs(1.0 / rayRow);
	if (rayCol == 0.0)
		*deltaCol = BIG;
	else
		*deltaCol = fabs(1.0 / rayCol);
	if (rayRow < 0.0)
	{
		*stepRow = -1;
		*sideDistRow = (pl->pos.x - *cellRow) * *deltaRow;
	}
	else
	{
		*stepRow = 1;
		*sideDistRow = (*cellRow + 1.0 - pl->pos.x) * *deltaRow;
	}
	if (rayCol < 0.0)
	{
		*stepCol = -1;
		*sideDistCol = (pl->pos.y - *cellCol) * *deltaCol;
	}
	else
	{
		*stepCol = 1;
		*sideDistCol = (*cellCol + 1.0 - pl->pos.y) * *deltaCol;
	}
}

/* boucle DDA : avance jusqu'au mur ;
renvoie hit + side_hit (false=row, true=col) */
bool	dda_advance_until_hit(t_game *g,
	int *cellRow, int *cellCol,
	double *sideDistRow, double *sideDistCol,
	double deltaRow, double deltaCol,
	int stepRow, int stepCol,
	bool *side_hit_col)
{
	bool	hit;
	int		guard;

	hit = false;
	guard = g->width * g->height + 8; // map pas ferm ???
	while (hit == false && guard > 0)
	{
		if (*sideDistRow < *sideDistCol)
		{
			*sideDistRow += deltaRow;
			*cellRow += stepRow;
			*side_hit_col = false;
		}
		else
		{
			*sideDistCol += deltaCol;
			*cellCol += stepCol;
			*side_hit_col = true;
		}
		if (is_wall(g, *cellRow, *cellCol) == true)
			hit = true;
		guard--;
	}
	return (hit);
}

/* distance perpendiculaire depuis etat DDA et le side_hit */
double dda_perp_distance(
	bool side_hit_col,
	double sideDistRow, double deltaRow,
	double sideDistCol, double deltaCol)
{
	double	perp;

	if (side_hit_col == false)
		perp = sideDistRow - deltaRow;
	else
		perp = sideDistCol - deltaCol;
	if (perp <= 0.0)
		perp = 0.0001;
	return (perp);
}

/*
                         ^ dir = (-1, 0)
                         |
        plane (-0.66, 0) | (0.66, 0)
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


