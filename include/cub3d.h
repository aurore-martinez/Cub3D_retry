/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:06:04 by eieong            #+#    #+#             */
/*   Updated: 2025/11/19 14:23:41 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ==========================	 📚 INCLUDE	 ========================== */
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_fprintf/ft_fprintf.h"
# include "../lib/gnl/get_next_line_bonus.h"
# include "../lib/libft/libft.h"
# include "../minilibx/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
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

# define BIG 4.2e42
/* Taille fixe des textures murales */
# define TEX_SIZE 256

# define SCR_W 960
# define SCR_H 640
// # define SCR_W 1920
// # define SCR_H 1080

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
// int mlx_get_color_value(t_xvar *xvar,int color)? voir use col.c ??

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

/* indices de carte */
typedef struct s_pos
{
	int	x;
	int	y;
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
	t_dpos	dir;
	t_dpos	plane;
} 	 t_vec;

typedef struct s_game
{
	t_element	elements;
	char		**map;
	t_pos		player; /* spawn */
	int			player_char;
	int			fd;
	int			width;
	int			height;
}	t_game;

/* pixel	*/
typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

/* Cam 2D (mini-map), issue de FdF */
typedef struct s_cam
{
	float	zoom; // init mais pas utilise
	int		x_offset;
	int		y_offset;
	int		color; // init mais pas utilise
	int		z_scale; // init mais pas utilise
	int		tile_size;
	bool	show_full_minimap;
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

typedef struct s_tex
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	int		width;
	int		height;
}	t_tex;

/* Paramètres temporaires pour dessiner une colonne texturée */
typedef struct s_tex_params
{
	void	*texture;
	int		tex_x;     /* coordonnée X dans la texture */
	int		line_h;    /* hauteur en pixels de la colonne mur à l'écran (clampée pour le dessin) */
	int		orig_line_h; /* hauteur originale calculée avant clamp (pour mapping) */
	int		tex_y_offset; /* offset Y (en pixels dans la texture) à appliquer si top a été tronqué */
	int		side;      /* 0: mur vertical, 1: mur horizontal (assombrir) */
}	t_tex_params;

typedef struct s_gfx
{
	void	*mlx;
	void	*win;
	t_img	frame;
	t_cam	cam;
	t_tex	texture;
}	t_gfx;

typedef struct s_keypress
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	mouse;
}	t_keypress;

typedef struct s_data
{
	t_game		*game;
	t_vec		player;
	t_gfx		*gfx;
	t_keypress	key;
	int			scr_w;
	int			scr_h;
	bool		need_redraw;
}	t_data;

typedef struct s_dda
{
	double	ray_row;
	double	ray_col;
	int		cell_row;
	int		cell_col;
	double	side_dist_row;
	double	side_dist_col;
	double	delta_row;
	double	delta_col;
	int		step_row;
	int		step_col;
	bool	side_hit_col;
}	t_dda;

/* REFACtO render.c*/
typedef struct s_render
{
	int		x;
	int		top;
	int		bot;
	int		line_h;
	int		side;
	double	perp;
}	t_render;

/* REFACTO accessorize.c*/
typedef struct s_fov_prep
{
	int		base_ts;
	int		r;
	int		p_row;
	int		p_col;
	int		start_row;
	int		start_col;
	int		player_screen_x;
	int		player_screen_y;
	double	zoom;
}	t_fov_prep;

/* ==============================     INIT    ============================ */
bool	init_mlx(t_gfx **gfx, int w, int h, const char *title);
bool	init_game(t_game **game, char *filename);
bool	init_data(t_data **data);
bool	init_player_from_game(t_data *data);
bool	set_camera(t_data *data);

/* ========================    🦄 PARSING    ======================== */
bool	check_map(t_game *game);
char	**line_to_map(t_game *game, char *line);
bool	check_line_char(t_game *game, char *line);
int		get_rgb(char *c_rgb);
bool	split_the_line(t_game *game, char *line);
bool	parse_floor_ceiling(t_game *game, char **element);
bool	parse_game_info(t_game *game);
bool	parse_wall(t_game *game, char **element);
bool	skip_line(char *line);
bool	has_all_element(t_game *game);
bool	is_line_for_map(char *line);

/* ==============================    🛠️ UTILS    ============================ */
void	gnl_clear(t_game *game, char *line);
void	clean_data(t_data *data);
void	print_error(char *str);
void	exit_error(char *str);

/* ========================	 🚧 DEBUG	 ======================== */
void	print_player_data(t_data *d);
void	print_game(t_game *g);
void	print_map(char **map);
void	print_dda(t_dda *r);
void	print_dda_init(t_dda *r);
void	print_dda_res_advance(t_dda *r, double perp, bool hit);
void	print_ray_debug(t_data *d, int column_index);

bool	handle_player_moves(t_data *d);

/* comprendre : cast 1 ray 1 col/wall */
bool	cast_ray_perp_dist(t_data *d, double cameraX, double *perp_dist, int *side_hit, int *out_row, int *out_col);
void	render_walls(t_data *d);

/*	======================== 🔦🦇 RAYCASTING ======================== */

/* calcule la direction du rayon pour une colonne caméra (cameraX in [-1,1]) */
void	ray_build_dir(const t_vec *pl, double cameraX, t_dda *r);
void	dda_init(const t_vec *pl, t_dda *r);
// bool	dda_advance_until_hit(t_game *g, t_dda *r);
/* avance la DDA (pour UN rayon preinit dans t_dda) */
bool	dda_advance_until_hit(t_game *g, t_dda *r);
double	dda_perp_distance(t_dda *r);
bool	is_wall(t_game *g, int row, int col);


/* ========================== 📊 GFX ========================== */
int		on_destroy_event(t_data *d);
void	draw_pixel(t_img *img, t_point p);
void	draw_hline(t_img *img, t_pos p0, int x1, int color);
void	draw_vline(t_img *img, t_pos p0, int y1, int color);
void	draw_col(t_data *d, t_pos start, int end, int color);
void	apply_walk(t_data *d, double nx, double ny, double margin);
void	turn_player(t_data *d, double angle);
int		render_frame(t_data *d);
int		on_key_press(int key, t_data *d);
int		on_key_release(int key, t_data *d);
void	draw_minimap(t_data *d);
void	draw_minimap_focus(t_data *d);
void	draw_crosshair(t_data *d);
void	draw_minimap_fov(t_data *d);
int		mm_tile_size(t_data *d);
int		mm_off_x(t_data *d);
int		mm_off_y(t_data *d);
int		mm_color_for_cell(t_data *d, char c);
int		mf_tile_size(t_data *d);
int		mf_off_x(t_data *d);
int		mf_off_y(t_data *d);
double	get_zoom_by_map_size(t_data *d);
double	mf_get_zoom_factor(t_data *d, int r, int base_ts);
int		on_mouse(int x, int y, t_data *d);
int		on_clic(int button, int x, int y, t_data *d);
bool	set_texture(t_data *data);
void	request_redraw(t_data *d);
int		loop_hook(t_data *d);

/* ========================== 🗺️ MINIMAP ========================== */
void	draw_minimap_cell(t_img *img, t_point cell, int size);
void	draw_player_disc(t_img *img, t_pos center, int radius, int color);

/* ========================== 🎨 TEXTURE ========================== */
int		get_texture_pixel(void *img, int x, int y);
int		darken_color(int color);
void	*select_texture(t_data *d, t_dda *ray, int side);
double	get_wall_x(t_data *d, t_dda *ray, double perp, int side);
int		get_texture_x(t_dda *ray, double wall_x, int side);
void	draw_textured_col(t_data *d, int x, int top, int bot,
					 t_tex_params *p);

#endif
