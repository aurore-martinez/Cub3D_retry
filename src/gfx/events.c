/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:30 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/04 15:46:20 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	init_mlx(t_gfx **gfx, int w, int h, const char *title)
{
	*gfx = malloc(sizeof(t_gfx));
	if (!(*gfx))
	{
		perror("Error");
		return (false);
	}
	(*gfx)->mlx = mlx_init();
	if ((*gfx)->mlx == NULL)
		return (false);
	(*gfx)->win = mlx_new_window((*gfx)->mlx, w, h, (char *)title);
	if ((*gfx)->win == NULL)
		return (false);
	(*gfx)->frame.img = mlx_new_image((*gfx)->mlx, w, h);
	if ((*gfx)->frame.img == NULL)
		return (false);
	(*gfx)->frame.addr = mlx_get_data_addr((*gfx)->frame.img, &(*gfx)->frame.bpp,
			&(*gfx)->frame.line_len, &(*gfx)->frame.endian);
	if ((*gfx)->frame.addr == NULL)
		return (false);
	return (true);
}

int	on_destroy_event(t_data *d)
{
	if (d == NULL)
		return (0);
	if (d->gfx->frame.img != NULL)
	{
		mlx_destroy_image(d->gfx->mlx, d->gfx->frame.img);
		d->gfx->frame.img = NULL;
	}
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
/* Fdf bonus*/
/* void	init_camera(t_camera *camera)
{
	camera->zoom = 1.0;
	camera->tile_size = 20;
	camera->z_scale = 1;
	camera->x_offset = WIN_WIDTH / 2;
	camera->y_offset = WIN_HEIGHT / 2;
	camera->color = 0xFFFFFF;
}
void	init_engine(t_engine *engine, char *filename)
{
	int	pixel_bits;
	int	line_len;
	int	endian;

	parse_map(filename, &engine->map);
	engine->mlx = mlx_init();
	if (!engine->mlx)
		error_message("[MLX ERROR]: can't init mlx!\n", 1);
	engine->window = mlx_new_window(engine->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	engine->image.img_ptr = mlx_new_image(engine->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!engine->window || !engine->image.img_ptr)
	{
		mlx_destroy_image(engine->mlx, engine->image.img_ptr);
		mlx_destroy_window(engine->mlx, engine->window);
		error_message("[MLX ERROR]: failed to create window/image!\n", 1);
	}
	engine->image.addr_ptr = mlx_get_data_addr(engine->image.img_ptr,
			&pixel_bits, &line_len, &endian);
	engine->image.pixel_bits = pixel_bits;
	engine->image.line_len = line_len;
	engine->image.endian = endian;
	init_camera(&engine->camera);
	engine->camera.z_scale = determine_z_scale(&engine->map);
	engine->camera.tile_size = determine_tile_size(&engine->map);
}

void	change_view(int key, t_engine *engine)
{
	if (key == KEY_LEFT)
		engine->camera.x_offset -= VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_RIGHT)
		engine->camera.x_offset += VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_UP)
		engine->camera.y_offset -= VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_DOWN)
		engine->camera.y_offset += VIEW_CHANGE_STEP / engine->camera.zoom;
	else if (key == KEY_PLUS)
		engine->camera.zoom *= ZOOM_FACTOR;
	else if (key == KEY_MINUS)
		engine->camera.zoom /= ZOOM_FACTOR;
	else if (key == KEY_1)
		engine->camera.z_scale += 1;
	else if (key == KEY_2)
		engine->camera.z_scale -= 1;
	else if (key == KEY_9)
		engine->camera.tile_size += 1;
	else if (key == KEY_0)
		engine->camera.tile_size -= 1;
} */
int	on_key_press(int key, t_data *d)
{
	if (key == KEY_ESC)
		on_destroy_event(d);
	/* gestions des touches */

/* 	else if (key == KEY_PLUS || key == KEY_MINUS
		|| key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_UP || key == KEY_DOWN
		|| key == KEY_1 || key == KEY_2
		|| key == KEY_9 || key == KEY_0)
		change_view(key, d); */

	render_frame(d);
	return (0);
}

