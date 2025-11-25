/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:59:42 by eieong            #+#    #+#             */
/*   Updated: 2025/11/25 11:27:16 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	atoi_rgb(char *c_rgb)
{
	int	rgb;

	if (!c_rgb || (*c_rgb) == '\n')
	{
		print_error("RGB syntax error");
		return (-1);
	}
	rgb = ft_atoi(c_rgb);
	if (ft_strlen(c_rgb) > 3 || rgb < 0 || rgb > 255)
	{
		print_error("RGB values must be between 0 and 255");
		return (-1);
	}
	return (rgb);
}

static int	count_split(char **split)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (split[i++])
		count++;
	return (count);
}

static char	*delete_newline(char *str)
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

int	get_rgb(char *c_rgb)
{
	char	**rgb_split;
	char	*tmp;
	t_rgb	rgb;

	tmp = delete_newline(c_rgb);
	if (!tmp)
		return (-1);
	rgb_split = ft_split(tmp, ',');
	free(tmp);
	if (!rgb_split)
		return (-1);
	if (count_split(rgb_split) != 3)
	{
		print_error("RGB syntax error");
		free_split(rgb_split);
		return (-1);
	}
	rgb.red = atoi_rgb(rgb_split[0]);
	rgb.green = atoi_rgb(rgb_split[1]);
	rgb.blue = atoi_rgb(rgb_split[2]);
	free_split(rgb_split);
	if (rgb.red == -1 || rgb.green == -1 || rgb.blue == -1)
		return (-1);
	return (rgb.red << 16 | rgb.green << 8 | rgb.blue);
}
