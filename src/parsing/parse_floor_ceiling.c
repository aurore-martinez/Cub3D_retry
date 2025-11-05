/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:37:01 by eieong            #+#    #+#             */
/*   Updated: 2025/10/31 16:01:21 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	parse_ceiling(t_game *game, char *path)
{
	(void) path; //change var name
	if (game->elements.ceiling)
	{
		print_error("Ceiling texture already parsed");
		return (false);
	}
	else
	{
		game->elements.ceiling = true;
		// game->elements.ceiling_texture ?????
	}
	return (true);
}

static bool	parse_floor(t_game *game, char *path)
{
	(void) path; //change var name
	if (game->elements.floor)
	{
		print_error("Floor texture already parsed");
		return (false);
	}
	else
	{
		game->elements.floor = true;
		// game->elements.floor_texture ?????
	}
	return (true);
}

bool	parse_floor_ceiling(t_game *game, char **element)
{
	if (!ft_strncmp(element[0], "F", INT_MAX))
	{
		if (!parse_floor(game, element[1]))
			return (false);
	}
	else if (!ft_strncmp(element[0], "C", INT_MAX))
	{
		if (!parse_ceiling(game, element[1]))
			return (false);
	}
	return (true);
}
