/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 10:49:43 by scros             #+#    #+#             */
/*   Updated: 2020/12/12 15:17:48 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	argptr;
	char	*str;

	va_start(argptr, format);
	while ((str = ft_strchr(format, '%')))
	{
		write(1, format, str - format);
		format = str + 1;
		format += ft_parser((char *)format, argptr);
	}
	ft_putstr_fd((char *)format, 1);
	return (0);
}
