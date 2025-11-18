/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessorize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:00:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/18 16:30:24 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Croix */
void	draw_crosshair(t_data *d)
{
	int	midy;
	int	midx;

	if (!d || !d->gfx)
		return ;
	midy = d->scr_h / 2;
	midx = d->scr_w / 2;
	draw_hline(&d->gfx->frame, (t_pos){midx - 15, midy}, midx - 5,
		UI_CROSSHAIR_COLOR);
	draw_hline(&d->gfx->frame, (t_pos){midx + 5, midy}, midx + 15,
		UI_CROSSHAIR_COLOR);
	draw_vline(&d->gfx->frame, (t_pos){midx, midy - 15}, midy - 5,
		UI_CROSSHAIR_COLOR);
	draw_vline(&d->gfx->frame, (t_pos){midx, midy + 5}, midy + 15,
		UI_CROSSHAIR_COLOR);
}

/* Calcule angle Rayon cOne FOV: voir minimap_utils.c */

/* center en mode minimap focus/zoom */
static void	fov_prepare_full_center(t_data *d, t_fov_prep *p,
				int *ts, t_pos *center)
{
	p->zoom = mf_get_zoom_factor(d, p->r, p->base_ts);
	*ts = (int)(p->base_ts * p->zoom);
	p->player_screen_x = (int)d->player.pos.y - p->start_col;
	p->player_screen_y = (int)d->player.pos.x - p->start_row;
	center->x = 20 + p->player_screen_x * (*ts) + (*ts) / 2;
	center->y = 20 + p->player_screen_y * (*ts) + (*ts) / 2;
}

/* prep ts et centre selon mode minimap */
static void	fov_prepare(t_data *d, int *ts, t_pos *center)
{
	t_fov_prep	p;

	p.base_ts = mm_tile_size(d);
	if (d->gfx->cam.show_full_minimap)
	{
		p.r = 8;
		p.p_row = (int)d->player.pos.x;
		p.p_col = (int)d->player.pos.y;
		p.start_row = p.p_row - p.r;
		if (p.start_row < 0)
			p.start_row = 0;
		p.start_col = p.p_col - p.r;
		if (p.start_col < 0)
			p.start_col = 0;
		fov_prepare_full_center(d, &p, ts, center);
	}
	else
	{
		*ts = p.base_ts;
		center->x = mm_off_x(d)
			+ (int)(d->player.pos.y * (*ts) + 0.5);
		center->y = mm_off_y(d)
			+ (int)(d->player.pos.x * (*ts) + 0.5);
	}
}

/* trace un rayon depuis center avec angle ang et longueur len */
static void	fov_draw_one(t_data *d, t_pos center, double len, double ang)
{
	t_dpos	dir;
	t_dpos	cur;
	int		i;
	t_point	p;

	dir.x = cos(ang);
	dir.y = sin(ang);
	cur.x = center.x;
	cur.y = center.y;
	i = 0;
	while (i < (int)len)
	{
		p.x = (int)(cur.x + dir.x * i);
		p.y = (int)(cur.y + dir.y * i);
		p.color = UI_FOV_COLOR;
		draw_pixel(&d->gfx->frame, p);
		i++;
	}
}

/* dessin rayon FOV */
void	draw_minimap_fov(t_data *d)
{
	int		ts;
	t_pos	c;
	int		i;
	double	len;

	if (!d || !d->gfx)
		return ;
	fov_prepare(d, &ts, &c);
	len = ts * 1.5;
	i = 0;
	while (i < 13)
	{
		fov_draw_one(d, c, len, calculate_ray_angle(d, i, 13));
		i++;
	}
}
