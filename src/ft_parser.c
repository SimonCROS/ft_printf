/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:59:23 by scros             #+#    #+#             */
/*   Updated: 2020/12/13 15:57:42 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_modifiers	*new_modifiers(void)
{
	t_modifiers *modifiers;

	if (!(modifiers = calloc(1, sizeof(t_modifiers))))
		return (NULL);
	if (!(modifiers->flags = calloc(1, sizeof(t_flags))))
	{
		free(modifiers);
		return (NULL);
	}
	return (modifiers);
}

static void			read_flags(char **str, t_flags *flags)
{
	int pos;

	while (**str && (pos = ft_strindex_of("-+ #0", **str)) != -1)
		*((char*)flags + pos) = !!*((*str)++);
}

static void			read_char(char **str, char *dest, char *possibilities)
{
	if (ft_strindex_of(possibilities, **str) != -1)
		*dest = *((*str)++);
}

static void			read_number(char **str, int *dest, va_list args)
{
	int len;

	if (**str == '*' && (len = 1))
		*dest = ft_max(-1, va_arg(args, int));
	else
		*dest = ft_atoi_len(*str, &len);
	(*str) += len;
}

int					ft_parser(const char *string, va_list args)
{
	t_modifiers *modifiers;
	char		*cpy;

	cpy = (char *)string;
	if (!(modifiers = new_modifiers()))
		return (-1);
	read_flags(&cpy, modifiers->flags);
	read_number(&cpy, &(modifiers->min_width), args);
	if (*cpy == '.' && *(++cpy))
		read_number(&cpy, &(modifiers->precision), args);
	read_char(&cpy, &(modifiers->read_as), "FNhlL");
	read_char(&cpy, &(modifiers->type), "diouxXfFeEgGaAcsb%");
	ft_applyer(modifiers, args);
	free(modifiers->flags);
	free(modifiers);
	return (cpy - string);
}
