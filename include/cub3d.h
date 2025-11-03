/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:06:04 by eieong            #+#    #+#             */
/*   Updated: 2025/11/03 17:39:38 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_fprintf/ft_fprintf.h"
# include "../lib/gnl/get_next_line_bonus.h"
# include "../lib/libft/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

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
	//RGB floor & ceiling, check 42 doc
}	t_element;

typedef struct s_game
{
	t_element		elements;
	char			**map;
	t_pos			player;
	int				player_char;
	int				fd;
	int				width;
	int				height;
}	t_game;

/* coord reelles du player, rayons, direction */
typedef struct s_dpos
{
	double	x;
	double	y;
}	t_dpos;

/* ensemble des vecteurs camera / player */
typedef struct s_player
{
	t_dpos	pos;	// position reelle dans la map
	t_dpos	dir;	// dir
	t_dpos	plane;	// plan camera pour champ de vision
}	t_player;

typedef struct s_data
{

}	t_data;

\
/* check_element.c */
bool	split_the_line(t_game *game, char *line);

/* check_map.c */
bool	check_map(t_game *game);

/* cleanup.c */
void	gnl_clear(t_game *game, char *line);
void	clean_game(t_game *game);

/* line_to_map.c */
char	**line_to_map(t_game *game, char *line);
bool	check_line_char(t_game *game, char *line);

/* parse_element1.c */
bool	parse_floor_ceiling(t_game *game, char **element);

/* parse_element.c */
bool	parse_wall(t_game *game, char **element);

/* parse_game_info.c */
bool	parse_game_info(t_game *game);

/* print_error.c */
void	print_error(char *str);
void	exit_error(char *str);

/* debug.c */
void	print_map(char **map);

#endif
