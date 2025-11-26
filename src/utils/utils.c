/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:37:27 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/26 15:06:38 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*delete_newline(char *str)
{
	char	*new;
	int		len;

	len = ft_strlen(str) - 1;
	if (str[len] == '\n')
	{
		new = malloc(sizeof(char) * (len + 1));
		if (!new)
		{
			ft_fprintf(2, "Error\n");
			perror("Malloc");
			return (NULL);
		}
		ft_memcpy(new, str, len);
		new[len] = '\0';
		return (new);
	}
	else
	{
		new = ft_strdup(str);
		return (new);
	}
}

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_wall(t_game *g, int row, int col)
{
	if (g == NULL)
		return (true);
	if (g->map == NULL)
		return (true);
	if (row < 0 || col < 0)
		return (true);
	if (row >= g->height || col >= g->width)
		return (true);
	if (g->map[row] == NULL)
		return (true);
	if ((int)ft_strlen(g->map[row]) <= col)
		return (true);
	if (g->map[row][col] == '1')
		return (true);
	return (false);
}
