/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 10:49:43 by scros             #+#    #+#             */
/*   Updated: 2020/12/18 17:23:49 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	read_flags(char **str, t_flags *flags)
{
	int pos;

	while (**str && (pos = ft_strindex_of("-+ #0", **str)) != -1)
		*((char*)flags + pos) = *((*str)++);
}

static void	read_char(char **str, char *dest, char *possibilities)
{
	if (ft_strindex_of(possibilities, **str) != -1)
		*dest = *((*str)++);
}

static int	read_number(char **str, int *dest, va_list args)
{
	int len;

	if (**str == '*' && (len = 1))
		*dest = va_arg(args, int);
	else
		*dest = ft_atoi_len(*str, &len);
	(*str) += len;
	return (*(*str - len) == '*');
}

static int	ft_parser(char **string, va_list args)
{
	t_modifiers para;
	char		second;

	ft_bzero(&para, sizeof(para));
	read_flags(string, &(para.flags));
	read_number(string, &(para.min_width), args);
	if (para.min_width < 0)
	{
		para.flags.left_align = '-';
		para.min_width *= -1;
	}
	if (**string == '.' && *(++(*string)))
		if (!read_number(string, &(para.prec), args) || para.prec >= 0)
			para.has_prec = 1;
	read_char(string, &(para.read_as), "hl");
	read_char(string, &(second), "hl");
	if (second == para.read_as)
		para.read_as++;
	read_char(string, &(para.type), "cspdiuxX%");
	return (ft_applyer(para, args));
}

int			ft_printf(const char *format, ...)
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
