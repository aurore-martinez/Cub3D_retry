/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessorize_fov.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:12:31 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 11:29:43 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Calcule angle Rayon cOne FOV */
/* Calcule l'angle du i-eme rayon dans le FOV du joueur */
static double	calculate_ray_angle(t_data *d, int ray_idx, int num_rays)
{
	double	fov;
	double	angle_start;
	double	angle_step;
	double	player_angle;

	fov = 1.047;
	player_angle = atan2(d->player.dir.x, d->player.dir.y);
	angle_start = player_angle - fov / 2.0;
	angle_step = fov / (double)(num_rays - 1);
	return (angle_start + ray_idx * angle_step);
}

/* centre en mode minimap focus/zoom (mêmes conversions que minimap_focus) */
static void	fov_prepare_full_center(t_data *d, int *ts, t_pos *center)
{
	*ts = mf_tile_size(d);
	center->x = mf_off_x(d) + (int)(d->player.pos.y * (*ts) + 0.5);
	center->y = mf_off_y(d) + (int)(d->player.pos.x * (*ts) + 0.5);
}

/* prep ts et centre selon mode minimap */
static void	fov_prepare(t_data *d, int *ts, t_pos *center)
{
	t_fov_prep	p;

	p.base_ts = mm_tile_size(d);
	if (d->gfx->cam.show_full_minimap)
		fov_prepare_full_center(d, ts, center);
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
