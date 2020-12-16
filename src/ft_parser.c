/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:59:23 by scros             #+#    #+#             */
/*   Updated: 2020/12/16 10:54:58 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			read_flags(char **str, t_flags *flags)
{
	int pos;

	while (**str && (pos = ft_strindex_of("-+ #0", **str)) != -1)
		*((char*)flags + pos) = *((*str)++);
}

static void			read_char(char **str, char *dest, char *possibilities)
{
	if (ft_strindex_of(possibilities, **str) != -1)
		*dest = *((*str)++);
}

static int			read_number(char **str, int *dest, va_list args)
{
	int len;

	if (**str == '*' && (len = 1))
		*dest = va_arg(args, int);
	else
		*dest = ft_atoi_len(*str, &len);
	(*str) += len;
	return (*(*str - len) == '*');
}

int					ft_parser(char **string, va_list args)
{
	t_modifiers modifiers;

	ft_bzero(&modifiers, sizeof(modifiers));
	read_flags(string, &(modifiers.flags));
	read_number(string, &(modifiers.min_width), args);
	if (modifiers.min_width < 0)
	{
		modifiers.flags.left_align = '-';
		modifiers.min_width *= -1;
	}
	if (**string == '.' && *(++(*string)))
		if (!read_number(string, &(modifiers.prec), args) || modifiers.prec > 0)
			modifiers.has_prec = 1;
	read_char(string, &(modifiers.read_as), "FNhlL");
	read_char(string, &(modifiers.type), "cspdiuxX%");
	return (ft_applyer(modifiers, args));
}
