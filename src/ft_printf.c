/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 10:49:43 by scros             #+#    #+#             */
/*   Updated: 2020/12/14 18:05:55 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	argptr;
	char	*from;
	char	*str;
	int		length;

	length = 0;
	from = (char *)format;
	va_start(argptr, format);
	while ((str = ft_strchr(from, '%')))
	{
		write(1, from, str - from);
		length += str - from;
		from = str + 1;
		length += ft_parser(&from, argptr);
	}
	length += ft_putstr_fd((char *)from, 1);
	return (length);
}
