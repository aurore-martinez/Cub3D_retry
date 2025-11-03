/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_game_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:42:41 by eieong            #+#    #+#             */
/*   Updated: 2025/10/31 16:09:23 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	skip_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else
			return (false);
	}
	return (true);
}

static bool	fill_map(t_game *game, char *line)
{
	if (skip_line(line))
		return (true);
	if (!check_line_char(game, line))
		return (false);
	game->height++;
	game->map = line_to_map(game, line);
	if (!game->map)
		return (false);
	return (true);
}

static bool	has_all_element(t_game *game)
{
	if (game->elements.north && game->elements.south
		&& game->elements.west && game->elements.east
		&& game->elements.floor && game->elements.ceiling)
		return (true);
	else
		return (false);
}

static bool	gnl_loop(t_game *game)
{
	char	*line;

	line = get_next_line(game->fd);
	if (!line)
		return (print_error("Empty file"), false);
	while (line)
	{
		if (!has_all_element(game))
		{
			if (!split_the_line(game, line))
				return (gnl_clear(game, line), false);
		}
		else
		{
			if (!fill_map(game, line))
				return (gnl_clear(game, line), false);
		}
		free(line);
		line = get_next_line(game->fd);
	}
	return (gnl_clear(game, line), true);
}

bool	parse_game_info(t_game *game)
{
	if (!gnl_loop(game))
		return (false);
	if (!has_all_element(game))
	{
		print_error("Some elements are missing");
		return (false);
	}
	return (true);
}
