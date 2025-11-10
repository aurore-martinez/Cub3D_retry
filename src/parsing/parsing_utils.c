/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:13:22 by eieong            #+#    #+#             */
/*   Updated: 2025/11/10 14:14:09 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	skip_line(char *line)
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

bool	has_all_element(t_game *game)
{
	if (game->elements.north && game->elements.south
		&& game->elements.west && game->elements.east
		&& game->elements.floor && game->elements.ceiling)
		return (true);
	else
		return (false);
}

bool	is_line_for_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'W'
			&& line[i] != 'E')
			return (false);
		i++;
	}
	return (true);
}
