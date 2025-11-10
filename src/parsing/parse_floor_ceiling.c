/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:37:01 by eieong            #+#    #+#             */
/*   Updated: 2025/11/10 14:32:05 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	check_comma(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (false);
	return (true);
}

static bool	parse_ceiling(t_game *game, char *c_rgb)
{
	if (game->elements.ceiling)
	{
		print_error("Ceiling color already parsed");
		return (false);
	}
	else if (!check_comma(c_rgb))
	{
		print_error("RGB syntax error");
		return (false);
	}
	else
	{
		game->elements.ceiling = true;
		game->elements.rgb_ceiling = get_rgb(c_rgb);
		if (game->elements.rgb_ceiling == -1)
			return (false);
	}
	return (true);
}

static bool	parse_floor(t_game *game, char *c_rgb)
{
	if (game->elements.floor)
	{
		print_error("Floor color already parsed");
		return (false);
	}
	else if (!check_comma(c_rgb))
	{
		print_error("RGB syntax error");
		return (false);
	}
	else
	{
		game->elements.floor = true;
		game->elements.rgb_floor = get_rgb(c_rgb);
		if (game->elements.rgb_floor == -1)
			return (false);
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
