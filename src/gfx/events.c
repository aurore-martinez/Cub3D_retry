/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:30 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/12 12:30:30 by eieong           ###   ########.fr       */
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

	/* délègue la logique de mouvement à la fonction dédiée */
	handle_player_moves(key, d);

	render_frame(d);
	return (0);
}

