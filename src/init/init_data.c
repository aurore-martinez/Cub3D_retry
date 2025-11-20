/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:35:49 by eieong            #+#    #+#             */
/*   Updated: 2025/11/20 14:51:07 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* init game */
bool	init_game(t_game **game, char *filename)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
	{
		ft_fprintf(2, "Error\n");
		perror("Malloc");
		return (false);
	}
	ft_memset(*game, 0, sizeof(t_game));
	(*game)->fd = open(filename, O_RDONLY);
	if ((*game)->fd < 0)
	{
		print_error("Failed to open file");
		free(*game);
		*game = NULL;
		return (false);
	}
	return (true);
}

/* “player” {0} */
static void	zero_player(t_vec *p)
{
	p->pos.x = 0.0;
	p->pos.y = 0.0;
	p->dir.x = 0.0;
	p->dir.y = 0.0;
	p->plane.x = 0.0;
	p->plane.y = 0.0;
}

static void	init_keypress(t_keypress *key)
{
	key->w = false;
	key->a = false;
	key->s = false;
	key->d = false;
	key->up = false;
	key->down = false;
	key->left = false;
	key->right = false;
	key->mouse = false;
}

/* init data */
bool	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
	{
		ft_fprintf(2, "Error\n");
		perror("Malloc");
		return (false);
	}
	ft_memset(*data, 0, sizeof(t_data));
	(*data)->game = NULL;
	(*data)->gfx = NULL;
	(*data)->scr_w = SCR_W;
	(*data)->scr_h = SCR_H;
	zero_player(&(*data)->player);
	init_keypress(&(*data)->key);
	(*data)->need_redraw = true;
	return (true);
}
