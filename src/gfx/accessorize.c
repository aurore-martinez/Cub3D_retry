/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessorize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:00:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/16 17:08:33 by aumartin         ###   ########.fr       */
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
	draw_hline(&d->gfx->frame, midy, midx - 15, midx - 5, UI_CROSSHAIR_COLOR);
	draw_hline(&d->gfx->frame, midy, midx + 5, midx + 15, UI_CROSSHAIR_COLOR);
	draw_vline(&d->gfx->frame, midx, midy - 15, midy - 5, UI_CROSSHAIR_COLOR);
	draw_vline(&d->gfx->frame, midx, midy + 5, midy + 15, UI_CROSSHAIR_COLOR);
}

/* Calcule angle Rayon cOne FOV */
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

/* range pour adapter le facteur des cases */
double	mf_get_zoom_factor(t_data *d, int r, int base_ts)
{
	int		crop_w;
	int		crop_h;
	double	zoom;
	double	max_zoom;
	int		available_w;
	int		available_h;

	zoom = get_zoom_by_map_size(d);
	available_w = d->scr_w - 40;
	available_h = d->scr_h - 40;
	crop_w = (r * 2 + 1) * base_ts * zoom;
	crop_h = (r * 2 + 1) * base_ts * zoom;
	while ((crop_w > available_w || crop_h > available_h) && zoom > 1.0)
	{
		zoom -= 0.1;
		crop_w = (r * 2 + 1) * base_ts * zoom;
		crop_h = (r * 2 + 1) * base_ts * zoom;
	}
	if (zoom < 1.0)
		zoom = 1.0;
	max_zoom = 2.5;
	if (zoom > max_zoom)
		zoom = max_zoom;
	return (zoom);
}

/* dessin rayon FOV */
void	draw_minimap_fov(t_data *d)
{
	int		ts;
	int		cx;
	int		cy;
	int		num_rays;
	int		i;
	double	ray_angle;
	double	length;
	t_point	p0;
	t_point	p1;

	int		r;
	int		p_row;
	int		p_col;
	int		start_row;
	int		start_col;
	int		player_screen_x;
	int		player_screen_y;
	int		base_ts;
	double	zoom;

	if (!d || !d->gfx)
		return ;
	base_ts = mm_tile_size(d);
	if (d->gfx->cam.show_full_minimap)
	{
		r = 8;
		p_row = (int)(d->player.pos.x);
		p_col = (int)(d->player.pos.y);
		start_row = p_row - r;
		if (start_row < 0)
			start_row = 0;
		start_col = p_col - r;
		if (start_col < 0)
			start_col = 0;
		zoom = mf_get_zoom_factor(d, r, base_ts);
		ts = (int)(base_ts * zoom);
		player_screen_x = (int)(d->player.pos.y) - start_col;
		player_screen_y = (int)(d->player.pos.x) - start_row;
		cx = 20 + player_screen_x * ts + ts / 2;
		cy = 20 + player_screen_y * ts + ts / 2;
	}
	else
	{
		ts = base_ts;
		cx = mm_off_x(d) + (int)(d->player.pos.y * ts + 0.5);
		cy = mm_off_y(d) + (int)(d->player.pos.x * ts + 0.5);
	}
	num_rays = 13;
	length = ts * 1.5;
	i = 0;
	while (i < num_rays)
	{
		ray_angle = calculate_ray_angle(d, i, num_rays);
		p0.x = cx;
		p0.y = cy;
		p0.z = 0;
		p0.color = UI_FOV_COLOR;
		p1.x = cx + (int)(cos(ray_angle) * length);
		p1.y = cy + (int)(sin(ray_angle) * length);
		p1.z = 0;
		p1.color = UI_FOV_COLOR;
		draw_line(&d->gfx->frame, p0, p1);
		i++;
	}
}
