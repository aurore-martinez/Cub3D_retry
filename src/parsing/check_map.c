/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:01:59 by eieong            #+#    #+#             */
/*   Updated: 2025/11/20 12:02:51 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	flood_fill(char **map, t_pos pos, t_game *game)
{
	if ((pos.y < 0 || pos.x < 0 || pos.x >= game->width
			|| pos.y >= game->height) || map[pos.y][pos.x] == ' ')
		return (false);
	else if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'X')
		return (true);
	map[pos.y][pos.x] = 'X';
	if (!flood_fill(map, (t_pos){pos.x - 1, pos.y}, game)
		|| !flood_fill(map, (t_pos){pos.x + 1, pos.y}, game)
		|| !flood_fill(map, (t_pos){pos.x, pos.y + 1}, game)
		|| !flood_fill(map, (t_pos){pos.x, pos.y - 1}, game))
		return (false);
	return (true);
}

static char	**dup_map(t_game *game)
{
	char	**mapcopy;
	int		i;

	i = 0;
	mapcopy = malloc(sizeof(char *) * (game->height + 1));
	if (!mapcopy)
		return (NULL);
	while (i < game->height)
	{
		mapcopy[i] = ft_strdup(game->map[i]);
		if (!mapcopy[i])
			return (NULL);
		i++;
	}
	mapcopy[i] = NULL;
	return (mapcopy);
}

static bool	is_map_valid(t_game *game)
{
	char	**map_copy;

	if (!game->player_char)
	{
		print_error("Player character is missing");
		return (false);
	}
	map_copy = dup_map(game);
	if (!map_copy)
		return (false);
	if (!flood_fill(map_copy, game->player, game))
	{
		free_split(map_copy);
		print_error("The playable area must be enclosed by walls");
		return (false);
	}
	free_split(map_copy);
	return (true);
}

static bool	fill_short_line(t_game *game)
{
	int		y;
	char	*tmp_line;

	y = 0;
	while (y < game->height)
	{
		if ((int)ft_strlen(game->map[y]) < game->width)
		{
			tmp_line = game->map[y];
			game->map[y] = malloc(sizeof(char) * (game->width + 1));
			if (!game->map[y])
			{
				perror("Error");
				game->map[y] = tmp_line;
				return (false);
			}
			ft_memset(game->map[y], ' ', game->width);
			ft_memcpy(game->map[y], tmp_line, ft_strlen(tmp_line));
			game->map[y][game->width] = '\0';
			free(tmp_line);
		}
		y++;
	}
	return (true);
}

bool	check_map(t_game *game)
{
	if (!game->map)
	{
		print_error("Empty map");
		return (false);
	}
	if (!fill_short_line(game))
		return (false);
	if (!is_map_valid(game))
		return (false);
	return (true);
}
