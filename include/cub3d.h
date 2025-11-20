/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:06:04 by eieong            #+#    #+#             */
/*   Updated: 2025/11/20 13:03:23 by eieong           ###   ########.fr       */
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

/* # define SCR_W 960
# define SCR_H 640 */
# define SCR_W 1280
# define SCR_H 720

# define MOVE_SPEED 0.15
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
}	t_element;

/* coord reelles du player, rayons, direction */
typedef struct s_dpos
{
	double	x;
	double	y;
}	t_dpos;

/* ensemble des vecteurs camera = player
pos = position reelle dans la map */
typedef struct s_vec
{
	t_dpos	pos;
	t_dpos	dir;
	t_dpos	plane;
}	t_vec;

/* player = spawn */
typedef struct s_game
{
	t_element	elements;
	char		**map;
	t_pos		player;
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
	int		x_offset;
	int		y_offset;
	int		tile_size;
	bool	show_full_minimap;
}	t_cam;

/*
	start = cellule haut-gauche (row=x, col=y)
	end = cellule bas-droite
	crop = decalage pixel (off_x/off_y ou 20/20 focus)
	ts = tile_size = taille tuile (pixels)
*/
typedef struct s_mview
{
	t_pos	start;
	t_pos	end;
	t_pos	crop;
	int		ts;
}	t_mview;

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

/* Param temp pour dessiner une colonne texturee */
/*
	tex_x = coordonnée X dans la texture
	line_h =  hauteur en pixels de la colonne mur a screen (clamp pour draw)
	orig_line_h = hauteur originale calculee avant clamp (pour mapping)
	tex_y_offset = offset Y (en pix dans la texture) apply si top tronque
	side =  mur vertical, 1: mur horizontal (assombrir)
*/
typedef struct s_tex_params
{
	void	*texture;
	int		tex_x;
	int		line_h;
	int		orig_line_h;
	int		tex_y_offset;
	int		side;
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

/* =============================   🦄 PARSING   ============================= */
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
bool	test_file(char *path);

/* ==============================     ⚙️ INIT    ============================ */
bool	init_mlx(t_gfx **gfx, int w, int h, const char *title);
bool	init_game(t_game **game, char *filename);
bool	init_data(t_data **data);
bool	init_player_from_game(t_data *data);
bool	set_camera(t_data *data);
bool	set_texture(t_data *data);

/* ========================    🔦🦇 RAYCASTING    ======================== */
void	ray_build_dir(const t_vec *pl, double cameraX, t_dda *r);
void	dda_init(const t_vec *pl, t_dda *r);
bool	dda_advance_until_hit(t_game *g, t_dda *r);
double	dda_perp_distance(t_dda *r);

/* ============================    📊 GFX    ============================ */
void	draw_crosshair(t_data *d);
int		darken_color(int color);
void	draw_pixel(t_img *img, t_point p);
void	draw_hline(t_img *img, t_pos p0, int x1, int color);
void	draw_vline(t_img *img, t_pos p0, int y1, int color);
void	draw_col(t_data *d, t_pos start, int end, int color);
void	request_redraw(t_data *d);
void	render_walls(t_data *d);
int		render_frame(t_data *d);

/* ===========================    🎨 TEXTURE    =========================== */
void	*select_texture(t_data *d, t_dda *ray, int side);
double	get_wall_x(t_data *d, t_dda *ray, double perp, int side);
int		get_texture_x(t_dda *ray, double wall_x, int side);
void	draw_textured_col(t_data *d, t_render *r, t_tex_params *p);

/* ============================    🎮 EVENTS    =========================== */
int		on_destroy_event(t_data *d);
void	apply_walk(t_data *d, double nx, double ny, double margin);
void	turn_player(t_data *d, double angle);
int		on_key_press(int key, t_data *d);
int		on_key_release(int key, t_data *d);
int		on_mouse(int x, int y, t_data *d);
int		on_clic(int button, int x, int y, t_data *d);
int		loop_hook(t_data *d);
bool	handle_player_moves(t_data *d);

/* ==========================    🗺️ MINIMAP    ========================== */
int		mm_tile_size(t_data *d);
int		mm_off_x(t_data *d);
int		mm_off_y(t_data *d);
int		mm_color_for_cell(t_data *d, char c);
int		mf_tile_size(t_data *d);
int		mf_off_x(t_data *d);
int		mf_off_y(t_data *d);
void	draw_minimap_fov(t_data *d);
void	draw_minimap_cell(t_img *img, t_point cell, int size);
void	draw_player_disc(t_img *img, t_pos center, int radius, int color);
void	draw_minimap_focus(t_data *d);
void	draw_minimap(t_data *d);

/* ==============================    🛠️ UTILS    ============================ */
void	gnl_clear(t_game *game, char *line);
void	clean_data(t_data *data);
void	print_error(char *str);
void	exit_error(char *str);
bool	is_wall(t_game *g, int row, int col);

/* =============================    🚧 DEBUG    ============================= */
void	print_player_data(t_data *d);
void	print_game(t_game *g);
void	print_map(char **map);
void	print_dda(t_dda *r);
void	print_dda_init(t_dda *r);
void	print_dda_res_advance(t_dda *r, double perp, bool hit);
void	print_ray_debug(t_data *d, int column_index);

/* ========================    🤔 LEARN    ======================== */
/* comprendre : cast 1 ray 1 col/wall */
/* bool	cast_ray_perp_dist(t_data *d, double cameraX,
	double *perp_dist, int *side_hit, int *out_row, int *out_col); */
/* exemple de render_walls() avec textures : */
/* void render_walls_with_textures(t_data *d) */
// bool	dda_advance_until_hit(t_game *g, t_dda *r);
/* avance la DDA (pour UN rayon preinit dans t_dda) */

#endif
