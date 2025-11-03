/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:52:54 by eieong            #+#    #+#             */
/*   Updated: 2025/10/31 16:01:23 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	parse_north(t_game *game, char *path)
{
	int	path_len;

	if (game->elements.north)
	{
		print_error("North texture already parsed");
		return (false);
	}
	else
	{
		path_len = ft_strlen(path) - 1;
		game->elements.north = true;
		game->elements.path_north = ft_substr(path, 0, path_len);
	}
	return (true);
}

static bool	parse_south(t_game *game, char *path)
{
	int	path_len;

	if (game->elements.south)
	{
		print_error("South texture already parsed");
		return (false);
	}
	else
	{
		path_len = ft_strlen(path) - 1;
		game->elements.south = true;
		game->elements.path_south = ft_substr(path, 0, path_len);
	}
	return (true);
}

static bool	parse_west(t_game *game, char *path)
{
	int	path_len;

	if (game->elements.west)
	{
		print_error("West texture already parsed");
		return (false);
	}
	else
	{
		path_len = ft_strlen(path) - 1;
		game->elements.west = true;
		game->elements.path_west = ft_substr(path, 0, path_len);
	}
	return (true);
}

static bool	parse_east(t_game *game, char *path)
{
	int	path_len;

	if (game->elements.east)
	{
		print_error("East texture already parsed");
		return (false);
	}
	else
	{
		path_len = ft_strlen(path) - 1;
		game->elements.east = true;
		game->elements.path_east = ft_substr(path, 0, path_len);
	}
	return (true);
}

bool	parse_wall(t_game *game, char **element)
{
	if (!ft_strncmp(element[0], "NO", INT_MAX))
	{
		if (!parse_north(game, element[1]))
			return (false);
	}
	else if (!ft_strncmp(element[0], "SO", INT_MAX))
	{
		if (!parse_south(game, element[1]))
			return (false);
	}
	else if (!ft_strncmp(element[0], "WE", INT_MAX))
	{
		if (!parse_west(game, element[1]))
			return (false);
	}
	else if (!ft_strncmp(element[0], "EA", INT_MAX))
	{
		if (!parse_east(game, element[1]))
			return (false);
	}
	return (true);
}
