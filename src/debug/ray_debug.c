/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:00:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/07 09:32:49 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* summ init state du rayon */
void	print_dda_init(t_dda *r)
{
	if (!r)
		return ;
	printf("=== dda init ===\n");
	printf(" ray=(%.6f,%.6f) start_cell=(%d,%d)\n",
		r->ray_row, r->ray_col, r->cell_row, r->cell_col);
}

/* print dda summ apres advance */
void	print_dda_res_advance(t_dda *r, double perp, bool hit)
{
	int			hit_i;
	const char	*side;

	if (!r)
		return ;
	if (hit)
		hit_i = 1;
	else
		hit_i = 0;
	side = "row";
	if (r->side_hit_col)
		side = "col";
	printf("=== dda summ apres advance ===\n");
	printf(" result: hit=%d perp=%.6f cell=(%d,%d) side=%s\n",
		hit_i,
		perp,
		r->cell_row,
		r->cell_col,
		side);
}

/*
 * print char de la cel
 * determinee par r->cell_row et r->cell_col
 * si la cel est hors-limit ou la ligne est NULL,
 * affiche '?' pour char inconnu
 */
static void	print_map_char_at_hit(t_data *d, t_dda *r)
{
	char	ch;
	int		len;

	ch = '?';
	if (r->cell_row >= 0 && r->cell_col >= 0)
	{
		if (d->game->map[r->cell_row])
		{
			len = (int)ft_strlen(d->game->map[r->cell_row]);
			if (r->cell_col < len)
				ch = d->game->map[r->cell_row][r->cell_col];
		}
		printf(" map char at hit = %c\n", ch);
	}
}

/*
 * Routine de debug pour un rayon vertical (col screen) :
 * - construit la dir du rayon pour la col demandee
 * - init la DDA (position, step, side distances)
 * - avance la DDA jusqu un mur
 *  - affiche les infos (state DDA, cel hit, distance perp, side hit)
 *  - check bornes de col_index si invalide
 */
void	print_ray_debug(t_data *d, int column_index)
{
	t_dda	r;
	double	cameraX;
	double	perp;
	bool	hit;

	if (!d || !d->game || !d->gfx)
		return ;
	if (column_index < 0 || column_index >= d->scr_w)
	{
		printf("print_ray_debug: column_index %d out of range\n", column_index);
		printf(" valid range: 0 .. %d\n", d->scr_w - 1);
		return ;
	}
	cameraX = 2.0 * column_index / (double)d->scr_w - 1.0;
	ray_build_dir(&d->player, cameraX, &r);
	dda_init(&d->player, &r);
	printf("--- ray debug for column %d ---\n", column_index);
	printf(" cameraX=%.6f\n", cameraX);
	print_dda_init(&r);
	hit = dda_advance_until_hit(d->game, &r);
	perp = dda_perp_distance(&r);
	print_dda_res_advance(&r, perp, hit);
	print_map_char_at_hit(d, &r);
}
