/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:59:23 by scros             #+#    #+#             */
/*   Updated: 2020/12/12 17:33:18 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_modifiers	*new_modifiers(void)
{
	t_modifiers *modifiers;

	if (!(modifiers = calloc(1, sizeof(t_modifiers))))
		return (NULL);
	modifiers->min_width = -1;
	modifiers->precision = -1;
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
		*((char*)flags + pos) = *((*str)++);
}

static void			read_number(char **str, int *dest, va_list args)
{
	if (**str == '*')
	{
		(*str)++;
		*dest = ft_max(-1, va_arg(args, int));
		return ;
	}
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
	free(modifiers->flags);
	free(modifiers);
	return (cpy - string);
}
