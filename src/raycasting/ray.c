/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:37:27 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 12:46:53 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "../../include/cub3d.h"

/* var :
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

