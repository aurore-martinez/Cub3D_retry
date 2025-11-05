/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:14:56 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 15:50:56 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int render_frame(t_data *d)
{
	int midy;
	int midx;

	if (!d || !d->gfx)
		return (0);

	/* fond */
	clear_frame(&d->gfx->frame, d->scr_w, d->scr_h, MAP_BG);

	/* raycasting murs + sky + sol */
	render_walls(d);

	/* a sup */
	midy = d->scr_h / 2;
	midx = d->scr_w / 2;

	/* a sup : horizontale blanche au milieu */
	draw_hline(&d->gfx->frame, midy, 0, d->scr_w - 1, WHITE);

	/* a sup : verticale rouge au milieu */
	draw_vline(&d->gfx->frame, midx, 0, d->scr_h - 1, RED);

	/* minimap */
	draw_minimap(d);

	/* push à l’écran */
	mlx_put_image_to_window(d->gfx->mlx, d->gfx->win, d->gfx->frame.img, 0, 0);
	return (0);
}

void render_walls(t_data *d)
{
	int		x;
	double	cameraX;
	double	perp;
	int		side;
	int		hit_r;
	int		hit_c;
	int		line_h;
	int		top;
	int		bot;
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
			draw_col(d, x, 0, top - 1, SKY);

		// mur
		draw_col(d, x, top, bot, wall);

		// sol
		if (bot + 1 < d->scr_h)
			draw_col(d, x, bot + 1, d->scr_h - 1, FLOOR);

		x++;
	}
}

