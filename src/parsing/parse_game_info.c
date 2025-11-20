/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_game_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:42:41 by eieong            #+#    #+#             */
/*   Updated: 2025/11/20 13:22:04 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	fill_map(t_game *game, char *line)
{
	if (!check_line_char(game, line))
		return (false);
	game->height++;
	game->map = line_to_map(game, line);
	if (!game->map)
		return (false);
	return (true);
}

static bool	parse_line(t_game *game, char *line)
{
	bool	line_map;

	line_map = is_line_for_map(line);
	if (!has_all_element(game))
	{
		if (line_map)
		{
			print_error("Some elements are missing");
			return (false);
		}
		if (!split_the_line(game, line))
			return (false);
	}
	else
	{
		if (!fill_map(game, line))
			return (false);
	}
	return (true);
}

static bool	gnl_loop(t_game *game)
{
	char	*line;

	line = get_next_line(game->fd);
	if (!line)
		return (print_error("Empty file"), false);
	while (line)
	{
		if (skip_line(line) && !has_all_element(game))
		{
			free(line);
			line = get_next_line(game->fd);
			continue ;
		}
		if (!parse_line(game, line))
			return (gnl_clear(game, line), false);
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
