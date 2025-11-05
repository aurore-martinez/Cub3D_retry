/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:37:27 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 16:28:21 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_wall(t_game *g, int row, int col)
{
	if (g == NULL)
		return (true);
	if (g->map == NULL)
		return (true);
	if (row < 0 || col < 0)
		return (true);
	if (row >= g->height || col >= g->width)
		return (true);
	if (g->map[row] == NULL)
		return (true);
	if (g->map[row][col] == '1')
		return (true);
	return (false);
}

/* caster un rayon perpendiculaire a modif plus tard avec cam
et renvoyer le distance */
/* Return:	hit true/false
side_hit: si frontiere "row" franchie, 1 si "col" franchie. */

bool	cast_ray_perp_dist(t_data *d, double cameraX, double *perp_dist, int *side_hit, int *out_row, int *out_col)
{
	double	rayRow;
	double	rayCol;
	int		cellRow;
	int		cellCol;
	double	sideDistRow;
	double	sideDistCol;
	double	deltaRow;
	double	deltaCol;
	int		stepRow;
	int		stepCol;
	bool	hit;
	bool	side_col;

	if (d == NULL || d->game == NULL)
		return (false);
	if (perp_dist == NULL || side_hit == NULL)
		return (false);
	ray_build_dir(&d->player, cameraX, &rayRow, &rayCol);
	dda_init(&d->player, rayRow, rayCol, &cellRow, &cellCol, &deltaRow,
		&deltaCol, &stepRow, &stepCol, &sideDistRow, &sideDistCol);
	hit = dda_advance_until_hit(d->game, &cellRow, &cellCol, &sideDistRow,
			&sideDistCol, deltaRow, deltaCol, stepRow, stepCol, &side_col);
	if (hit == false)
		return (false);
	*perp_dist = dda_perp_distance(side_col, sideDistRow, deltaRow, sideDistCol, deltaCol);
	if (*side_hit == 0)
		*perp_dist = sideDistRow - deltaRow;
	else
		*perp_dist = sideDistCol - deltaCol;
	if (*perp_dist <= 0.0)
		*perp_dist = 0.0001;
	if (out_row != NULL)
		*out_row = cellRow;
	if (out_col != NULL)
		*out_col = cellCol;
	return (true);
}
