/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:09:24 by eieong            #+#    #+#             */
/*   Updated: 2025/11/20 12:43:20 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	last_char(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (i > game->width)
		game->width = i;
	return (line[i]);
}

static char	**copy_map(t_game *game, char *line, char **tmp)
{
	int	i;

	i = 0;
	tmp[game->height] = NULL;
	while (i < game->height - 1)
	{
		tmp[i] = game->map[i];
		i++;
	}
	if (last_char(game, line) == '\n')
		tmp[i] = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		tmp[i] = ft_strdup(line);
	if (!tmp[i])
	{
		ft_fprintf(2, "Error\n");
		return (perror ("Malloc"), NULL);
	}
	return (tmp);
}

char	**line_to_map(t_game *game, char *line)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (game->height + 1));
	if (!tmp)
	{
		ft_fprintf(2, "Error\n");
		return (perror ("Malloc"), NULL);
	}
	tmp = copy_map(game, line, tmp);
	if (game->map)
		free(game->map);
	return (tmp);
}

static bool	get_player_info(t_game *game, char *line, int i)
{
	if (game->player_char)
	{
		print_error("Only one player character required");
		return (false);
	}
	else
	{
		game->player.x = i;
		game->player.y = game->height;
		game->player_char = line[i];
	}
	return (true);
}

bool	check_line_char(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' ')
			i++;
		else if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (!get_player_info(game, line, i))
				return (false);
			i++;
		}
		else
			return (print_error("Invalid character"), false);
	}
	return (true);
}
