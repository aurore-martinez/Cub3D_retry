/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:25:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/18 15:00:46 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Calcule l'angle du i-eme rayon dans le FOV du joueur */
double	calculate_ray_angle(t_data *d, int ray_idx, int num_rays)
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
