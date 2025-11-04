/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:06:26 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 15:07:46 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* cameraX   = 2.0 * x / scr_w - 1.0;

Direction du rayon projetée dans l’espace monde (row/col)
rayRow    = player.dir.x   + player.plane.x   * cameraX;
rayCol    = player.dir.y   + player.plane.y   * cameraX;

Case de départ dans la grille
cellRow   = (int) player.pos.x;
cellCol   = (int) player.pos.y;

/* Distances “delta” (coût pour franchir une case dans chaque axe)
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
