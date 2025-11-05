/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:41:07 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 11:22:45 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* caster un rayon DDA et renvoyer le distance -> trouver mur */

static bool	is_wall(t_game *g, int row, int col)
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

static void	draw_wall_col(t_data *d, int x, int drawStart, int drawEnd, int color)
{
	int		y;
	t_point	p;

	if (!d || x < 0 || x >= d->scr_w)
		return ;
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= d->scr_h)
		drawEnd = d->scr_h - 1;
/* 	if (drawStart > drawEnd) // col vide ??
		return ; */
	y = drawStart;
	while (y <= drawEnd)
	{
		p.x = x;
		p.y = y;
		p.z = 0;
		p.color = color;
		draw_pixel(&d->gfx->frame, p);
		y++;
	}
}

/* caster un rayon et renvoyer le distance */
/* Return:	hit true/false
side_hit: 0 si frontiere "row" franchie, 1 si "col" franchie. */

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
	const double BIG = 1e30;

	if (d == NULL || d->game == NULL)
		return (false);
	if (perp_dist == NULL || side_hit == NULL)
		return (false);

	/* dir du rayon dans (row/col) */
	rayRow = d->player.dir.x + d->player.plane.x * cameraX;
	rayCol = d->player.dir.y + d->player.plane.y * cameraX;

	cellRow = (int)d->player.pos.x;
	cellCol = (int)d->player.pos.y;

	if (rayRow == 0.0)
		deltaRow = BIG;
	else
		deltaRow = fabs(1.0 / rayRow);
	if (rayCol == 0.0)
		deltaCol = BIG;
	else
		deltaCol = fabs(1.0 / rayCol);

	if (rayRow < 0.0)
	{
		stepRow = -1;
		sideDistRow = (d->player.pos.x - cellRow) * deltaRow;
	}
	else
	{
		stepRow = 1;
		sideDistRow = (cellRow + 1.0 - d->player.pos.x) * deltaRow;
	}
	if (rayCol < 0.0)
	{
		stepCol = -1;
		sideDistCol = (d->player.pos.y - cellCol) * deltaCol;
	}
	else
	{
		stepCol = 1;
		sideDistCol = (cellCol + 1.0 - d->player.pos.y) * deltaCol;
	}

	hit = false;
	while (hit == false)
	{
		if (sideDistRow < sideDistCol)
		{
			sideDistRow += deltaRow;
			cellRow += stepRow;
			*side_hit = 0;
		}
		else
		{
			sideDistCol += deltaCol;
			cellCol += stepCol;
			*side_hit = 1;
		}
		if (is_wall(d->game, cellRow, cellCol) == true)
			hit = true;
	}

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

/* dessiner UNE colonne  */
void render_walls(t_data *d)
{
	int		x;
	double	cameraX;
	double	perp;
	int		side;
	int		hit_r;
	int		hit_c;
	int		line_h, top, bot;
	int		sky    = SKY;
	int		floor = FLOOR;
	int		wall;

	x = 0;
	while (x < d->scr_w)
	{
		cameraX = 2.0 * x / (double)d->scr_w - 1.0;

		if (!cast_ray_perp_dist(d, cameraX, &perp, &side, &hit_r, &hit_c))
		{
			x++;
			continue ;
		}
		if (perp < 1e-6)
			perp = 1e-6;

		line_h = (int)(d->scr_h / perp);
		top = -line_h / 2 + d->scr_h / 2;
		bot =  line_h / 2 + d->scr_h / 2;
		if (top < 0)
			top = 0;
		if (bot >= d->scr_h)
			bot = d->scr_h - 1;

		if (side == 1)
			wall = WALL_MAIN;
		else
			wall = WALL_SHADOW;


		// plafond
		if (top > 0)
			draw_wall_col(d, x, 0, top - 1, sky);
		// mur
		draw_wall_col(d, x, top, bot, wall);
		// sol
		if (bot + 1 < d->scr_h)
			draw_wall_col(d, x, bot + 1, d->scr_h - 1, floor);

		x++;
	}
}

