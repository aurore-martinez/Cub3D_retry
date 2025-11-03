/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:21:20 by eieong            #+#    #+#             */
/*   Updated: 2025/11/03 14:23:54 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fprinthex(int fd, unsigned long n, const char format)
{
	int		count;
	char	*base;

	if (format == 'x' || format == 'p')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	if (n < 16)
		return (ft_fprintchar(fd, base[n]));
	else
	{
		count = ft_fprinthex(fd, (n / 16), format);
		return (count + ft_fprinthex(fd, (n % 16), format));
	}
}

int	ft_fprintdigit(int fd, long n)
{
	int		count;

	if (n < 0)
	{
		write(fd, "-", 1);
		return (ft_fprintdigit(fd, -n) + 1);
	}
	if (n < 10)
		return (ft_fprintchar(fd, n + '0'));
	else
	{
		count = ft_fprintdigit(fd, n / 10);
		return (count + ft_fprintdigit(fd, n % 10));
	}
}

int	fprint_format(int fd, const char format, va_list args)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_fprintchar(fd, va_arg(args, int));
	else if (format == 's')
		count += ft_fprintstr(fd, va_arg(args, char *));
	else if (format == 'p')
		count += ft_fprintptr(fd, va_arg(args, unsigned long), format);
	else if (format == 'd' || format == 'i')
		count += ft_fprintdigit(fd, va_arg(args, int));
	else if (format == 'u')
		count += ft_fprintdigit(fd, va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_fprinthex(fd, va_arg(args, unsigned int), format);
	else if (format == '%')
		count += ft_fprintpercent(fd);
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			count += fprint_format(fd, *(++format), args);
		else
			count += write(fd, format, 1);
		++format;
	}
	va_end(args);
	return (count);
}
