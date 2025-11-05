/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:25:24 by eieong            #+#    #+#             */
/*   Updated: 2025/11/05 12:46:53 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Prints "Error\n" + str\n
*/
void	print_error(char *str)
{
	ft_fprintf(2, "Error\n");
	if (str)
		ft_fprintf(2, "%s\n", str);
}

void	exit_error(char *str)
{
	print_error(str);
	exit(1);
}
