/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:47:22 by eieong            #+#    #+#             */
/*   Updated: 2025/11/26 15:05:50 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_valid_identifier(char *id)
{
	if (!ft_strncmp(id, "NO", INT_MAX)
		|| !ft_strncmp(id, "SO", INT_MAX)
		|| !ft_strncmp(id, "WE", INT_MAX)
		|| !ft_strncmp(id, "EA", INT_MAX)
		|| !ft_strncmp(id, "F", INT_MAX)
		|| !ft_strncmp(id, "C", INT_MAX))
		return (true);
	else
		return (false);
}

static bool	parse_element(t_game *game, char **element)
{
	if (!is_valid_identifier(element[0]))
	{
		ft_fprintf(2, "Error\n");
		ft_fprintf(2, "%s is not a valid identifier\n", element[0]);
		return (false);
	}
	else if (!parse_wall(game, element))
		return (false);
	else if (!parse_floor_ceiling(game, element))
		return (false);
	return (true);
}

static int	count_split_elem(char **split_tab)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (split_tab[i])
	{
		count++;
		i++;
	}
	if ((i > 0) && !ft_strncmp(split_tab[i - 1], "\n", INT_MAX))
		count--;
	return (count);
}

static bool	check_elem_errors(char **split_line)
{
	if (!split_line)
	{
		ft_fprintf(2, "Error\n");
		return (perror("Malloc"), false);
	}
	if (!split_line[0])
		return (true);
	if (count_split_elem(split_line) != 2)
	{
		print_error("Wrong element syntax");
		free_split(split_line);
		split_line = NULL;
		return (false);
	}
	return (true);
}

bool	split_the_line(t_game *game, char *line)
{
	char	**split_line;
	char	*tmp_line;

	if (!ft_isalpha(line[0]))
	{
		print_error("Wrong element syntax");
		return (false);
	}
	tmp_line = delete_newline(line);
	split_line = ft_split(tmp_line, ' ');
	free(tmp_line);
	if (!check_elem_errors(split_line))
		return (false);
	else if (split_line[0])
	{
		if (!parse_element(game, split_line))
		{
			free_split(split_line);
			split_line = NULL;
			return (false);
		}
	}
	free_split(split_line);
	split_line = NULL;
	return (true);
}
