/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:14:52 by scros             #+#    #+#             */
/*   Updated: 2020/12/15 15:45:01 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	final_len(t_modifiers para, char *s)
{
	int len;

	if (!s)
		return (0);
	if (para.has_prec)
		len = ft_min(ft_strlen(s), ft_abs(para.prec));
	else
		len = ft_strlen(s);
	return (ft_max(para.min_width, len));
}

static int	char_type(t_modifiers para, char c)
{
	char str[ft_max(1, para.min_width)];

	ft_memset(&str, ft_ternary(para.flags.left_align, ' ',
		ft_max(' ', para.flags.zero)), para.min_width);
	str[ft_ternary(para.flags.left_align, 0,
		ft_max(para.min_width - 1, 0))] = c;
	return (write(1, str, ft_max(1, para.min_width)));
}

static int	string_type(t_modifiers para, char *s)
{
	int		len;
	int		from;
	int		s_len;
	char	str[final_len(para, s)];

	if (!s)
		return (string_type(para, "(null)"));
	len = sizeof(str);
	s_len = ft_strlen(s);
	ft_memset(&str, ft_ternary(para.flags.left_align, ' ',
		ft_max(' ', para.flags.zero)), len);
	if (!para.has_prec || para.prec >= 0)
	{
		from = ft_ternary(para.has_prec, ft_min(s_len, para.prec), s_len);
		ft_strninsert(str, s, ft_ternary(para.flags.left_align, 0, len - from),
			from);
	}
	return (write(1, str, len));
}

static int	pointer_type(t_modifiers para, void *p)
{
	int				i;
	int				str_i;
	char			c;
	char			str[20];
	uint64_t		addr;

	i = 1;
	str_i = 2;
	addr = (uint64_t)p;
	ft_strlcpy(str, "0x", 3);
	while (i <= 16)
	{
		if (!((addr >> 4 * (16 - i)) % 16))
			i++;
		else
			break ;
	}
	while (i <= 16)
	{
		c = (addr >> 4 * (16 - i++)) % 16;
		str[str_i++] = (c > 9) ? 'a' + c - 10 : '0' + c;
	}
	str[str_i] = 0;
	return (string_type(para, str));
}

int			ft_applyer(t_modifiers para, va_list args)
{
	if (para.type == 'c')
		return (char_type(para, va_arg(args, int)));
	else if (para.type == '%')
		return (char_type(para, '%'));
	else if (para.type == 's')
		return (string_type(para, va_arg(args, char*)));
	else if (para.type == 'p')
		return (pointer_type(para, va_arg(args, void*)));
	return (0);
}
