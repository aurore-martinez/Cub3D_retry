/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:06:04 by eieong            #+#    #+#             */
/*   Updated: 2025/11/06 12:10:47 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ==========================    📚 INCLUDE    ========================== */
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_fprintf/ft_fprintf.h"
# include "../lib/gnl/get_next_line_bonus.h"
# include "../lib/libft/libft.h"
# include "../minilibx/minilibx-linux/mlx.h"
# include "keys.h"
# include "color.h"
# include "palette.h"
# include <limits.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define SCR_W 960
# define SCR_H 640
# define RGB(r, g, b) ((int)(((r) & 0xFF) << 16 | ((g) & 0xFF) << 8 | ((b) & 0xFF)))
// int mlx_get_color_value(t_xvar *xvar,int color) ??

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

/* indices de carte */
typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;

typedef struct s_element
{
	bool	north;
	bool	south;
	bool	west;
	bool	east;
	bool	floor;
	bool	ceiling;
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	int		rgb_floor;
	int		rgb_ceiling;
	//RGB floor & ceiling, check 42 doc
}	t_element;

/* coord reelles du player, rayons, direction */
typedef struct s_dpos
{
	double	x;
	double	y;
}	t_dpos;

/* ensemble des vecteurs camera = player */
typedef struct s_vec
{
	t_dpos	pos;	// position reelle dans la map
	t_dpos	dir;	// dir
	t_dpos	plane;	// plan camera pour champ de vision
}	t_vec;

typedef struct s_game
{
	t_element		elements;
	char			**map;
	t_pos			player; // spawn
	int				player_char;
	int				fd;
	int				width;
	int				height;
}	t_game;

/* === bresenham === */
typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_bresenham;

/* === pixel === */
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

/* Cam 2D (mini-map), issue de FdF */
typedef struct s_cam
{
	float	zoom;
	int		x_offset;
	int		y_offset;
	int		color;
	int		z_scale;
	int		tile_size;
}	t_cam;

/* MiniLibX */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_gfx
{
	void	*mlx;
	void	*win;
	t_img	frame;
	t_cam	cam;
}	t_gfx;

typedef struct s_data
{
	t_game	*game;
	t_vec	player;
	t_gfx	*gfx;
	int		scr_w;
	int		scr_h;
}	t_data;

/* ==============================     INIT    ============================ */
bool	init_mlx(t_gfx **gfx, int w, int h, const char *title);
bool	init_game(t_game **game, char *filename);
bool	init_data(t_data **data);
bool	init_player_from_game(t_data *data);

/* ========================    🦄 PARSING    ======================== */
bool	check_map(t_game *game);
char	**line_to_map(t_game *game, char *line);
bool	check_line_char(t_game *game, char *line);
int		get_rgb(char *c_rgb);
bool	split_the_line(t_game *game, char *line);
bool	parse_floor_ceiling(t_game *game, char **element);
bool	parse_game_info(t_game *game);
bool	parse_wall(t_game *game, char **element);

/* ==============================    🛠️ UTILS    ============================ */
void	gnl_clear(t_game *game, char *line);
void	clean_data(t_data *data);
void	print_error(char *str);
void	exit_error(char *str);

/* ========================    🚧 DEBUG    ======================== */
void	print_player_data(t_data *d);
void	print_game(t_game *g);
void	print_map(char **map);

/*  ======================== 🔦🦇 RAYCASTING ======================== */

/* ========================== 📊 GFX ========================== */
int		on_destroy_event(t_data *d);
void	draw_line(t_img *img, t_point a, t_point b_point);
void	draw_pixel(t_img *img, t_point p);
void	draw_hline(t_img *img, int y, int x0, int x1, int color);
void	draw_vline(t_img *img, int x, int y0, int y1, int color);
int		render_frame(t_data *d);
void	clear_frame(t_img *img, int w, int h, int color);
int		on_key_press(int key, t_data *d);
void	draw_minimap(t_data *d);

#endif
