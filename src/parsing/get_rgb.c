/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:59:42 by eieong            #+#    #+#             */
/*   Updated: 2025/11/05 15:41:17 by eieong           ###   ########.fr       */
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
		print_error("RGB values muste be between 0 and 255");
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
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
	{
		perror("Error");
		return (NULL);
	}
	ft_memcpy(new, str, len);
	new[len] = '\0';
	return (new);
}

int	get_rgb(char *c_rgb)
{
	char	**rgb_split;
	int		red;
	int		green;
	int		blue;

	c_rgb = delete_newline(c_rgb);
	if (!c_rgb)
		return (-1);
	rgb_split = ft_split(c_rgb, ',');
	if (!rgb_split)
		return (-1);
	if (count_split(rgb_split) != 3)
	{
		print_error("RGB syntax error");
		free_split(rgb_split);
		return (-1);
	}
	red = atoi_rgb(rgb_split[0]);
	green = atoi_rgb(rgb_split[1]);
	blue = atoi_rgb(rgb_split[2]);
	free_split(rgb_split);
	if (red == -1 || green == -1 || blue == -1)
		return (-1);
	return (red << 16 | green << 8 | blue);
}
