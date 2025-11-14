/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:30 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/14 15:32:02 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	on_destroy_event(t_data *d)
{
	if (d == NULL)
		return (0);
	if (d->gfx->frame.img != NULL)
	{
		mlx_destroy_image(d->gfx->mlx, d->gfx->frame.img);
		d->gfx->frame.img = NULL;
	}
	/* cette partie peut etre enlevee car deja clean_data*/
	if (d->gfx->win != NULL)
	{
		mlx_destroy_window(d->gfx->mlx, d->gfx->win);
		d->gfx->win = NULL;
	}
	if (d->gfx->mlx)
	{
		mlx_destroy_display(d->gfx->mlx);
		free(d->gfx->mlx);
		d->gfx->mlx = NULL;
	}
	clean_data(d);
	exit(EXIT_SUCCESS);
	return (0);
}

/* void	clear_frame(t_img *img, int w, int h, int color)
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
} */

int	on_key_press(int key, t_data *d)
{
	if (key == KEY_M && d && d->gfx)
	{
		d->gfx->cam.show_full_minimap = !d->gfx->cam.show_full_minimap;
		request_redraw(d);
		return (0);
	}
	if (key == KEY_ESC)
		on_destroy_event(d);
	handle_player_moves(key, d);
	request_redraw(d);
	return (0);
}

int	on_mouse(int x, int y, t_data *d)
{
	static int	last_x = -1;
	int		dx;
	double	angle;

	(void)y;
	if (!d)
		return (0);
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	dx = x - last_x;
	last_x = x;
	if (dx == 0)
		return (0);
	angle = (double)dx * 0.0035; /* radians per pixel */
	turn_player(d, -angle);
	request_redraw(d);
	return (0);
}

void	request_redraw(t_data *d)
{
	if (!d)
		return ;
	d->need_redraw = true;
}

int	loop_hook(t_data *d)
{
	if (!d)
		return (0);
	if (d->need_redraw)
	{
		render_frame(d);
		d->need_redraw = false;
	}
	return (0);
}
