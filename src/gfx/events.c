/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:30 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 14:22:21 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	init_mlx(t_data *d, const char *title)
{
	if (d == NULL)
		return (false);
	d->gfx.mlx = mlx_init();
	if (d->gfx.mlx == NULL)
		return (false);
	d->gfx.win = mlx_new_window(d->gfx.mlx, d->scr_w, d->scr_h, (char *)title);
	if (d->gfx.win == NULL)
		return (false);
	d->gfx.frame.img = mlx_new_image(d->gfx.mlx, d->scr_w, d->scr_h);
	if (d->gfx.frame.img == NULL)
		return (false);
	d->gfx.frame.addr = mlx_get_data_addr(d->gfx.frame.img, &d->gfx.frame.bpp,
			&d->gfx.frame.line_len, &d->gfx.frame.endian);
	if (d->gfx.frame.addr == NULL)
		return (false);
	return (true);
}

int	on_destroy_event(t_data *d)
{
	if (d == NULL)
		return (0);
	if (d->gfx.frame.img != NULL)
	{
		mlx_destroy_image(d->gfx.mlx, d->gfx.frame.img);
		d->gfx.frame.img = NULL;
	}
	if (d->gfx.win != NULL)
	{
		mlx_destroy_window(d->gfx.mlx, d->gfx.win);
		d->gfx.win = NULL;
	}
	if (d->gfx.mlx)
	{
		mlx_destroy_display(d->gfx.mlx);
		free(d->gfx.mlx);
		d->gfx.mlx = NULL;
	}
	clean_data(d);
	exit(EXIT_SUCCESS);
	return (0);
}

void	clear_frame(t_img *img, int w, int h, int color)
{
	int		x;
	int		y;
	t_point	p;

	if (img == NULL)
		return ;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			p.x = x;
			p.y = y;
			p.z = 0;
			p.color = color;
			draw_pixel(img, p);
			x++;
		}
		y++;
	}
}
int	on_key_press(int key, t_data *d)
{
	if (key == KEY_ESC)
		on_destroy_event(d);
	/* gestions des touches */
	render_frame(d);
	return (0);
}

