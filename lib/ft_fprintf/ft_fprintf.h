/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eieong <eieong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:08:54 by eieong            #+#    #+#             */
/*   Updated: 2025/04/28 14:56:58 by eieong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

int	ft_fprintf(int fd, const char *format, ...);
int	ft_fprintchar(int fd, int c);
int	ft_fprintstr(int fd, char *str);
int	ft_fprintdigit(int fd, long n);
int	ft_fprinthex(int fd, unsigned long n, const char format);
int	ft_fprintpercent(int fd);
int	ft_fprintptr(int fd, unsigned long n, const char format);

#endif
