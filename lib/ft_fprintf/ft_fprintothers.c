/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintothers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:17:32 by eieong            #+#    #+#             */
/*   Updated: 2025/11/03 14:23:58 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fprintchar(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_fprintstr(int fd, char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (*str)
	{
		ft_fprintchar(fd, (int)*str);
		count++;
		str++;
	}
	return (count);
}

int	ft_fprintpercent(int fd)
{
	return (write(fd, "%", 1));
}

int	ft_fprintptr(int fd, unsigned long n, const char format)
{
	int	count;

	count = 0;
	if (!n)
		return (write(fd, "(nil)", 5));
	else
	{
		count += write(fd, "0x", 2);
		count += ft_fprinthex(fd, n, format);
	}
	return (count);
}
