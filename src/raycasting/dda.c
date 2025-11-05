/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:41:07 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 12:46:53 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
