/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:37:27 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/06 12:15:22 by aumartin         ###   ########.fr       */
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
	/* protect against ragged lines: if column beyond actual line length, treat as wall */
	if ((int)ft_strlen(g->map[row]) <= col)
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
	t_dda	r;
	bool	hit;

	if (d == NULL || d->game == NULL)
		return (false);
	if (perp_dist == NULL || side_hit == NULL)
		return (false);

	/* build ray direction for this cameraX, then init DDA state */
	ray_build_dir(&d->player, cameraX, &r);
	dda_init(&d->player, &r);
	hit = dda_advance_until_hit(d->game, &r);
	if (hit == false)
		return (false);
	*perp_dist = dda_perp_distance(&r);
	if (side_hit != NULL)
		*side_hit = r.side_hit_col ? 1 : 0;
	if (*perp_dist <= 0.0)
		*perp_dist = 0.0001;
	if (out_row != NULL)
		*out_row = r.cell_row;
	if (out_col != NULL)
		*out_col = r.cell_col;
	return (true);
}
