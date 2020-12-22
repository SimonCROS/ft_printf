/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:14:52 by scros             #+#    #+#             */
/*   Updated: 2020/12/22 13:31:06 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	final_str_len(t_modifiers para, char *s)
{
	int len;

	if (!s)
		return (0);
	if (para.has_prec)
		len = ft_min(ft_strlen(s), ft_abs(para.prec));
	else
		len = ft_strlen(s);
	return (ft_max(para.min, len));
}

static int	char_type(t_modifiers para, char c)
{
	char	*str;
	int		ret;

	if (!(str = malloc(ft_max(1, para.min))))
		return (-1);
	ft_memset(str, (' ' | para.flags.zero) * !para.flags.left | ' ', para.min);
	str[!para.flags.left * ft_max(0, para.min - 1)] = c;
	ret = write(1, str, ft_max(1, para.min));
	free(str);
	return (ret);
}

int			string_type(t_modifiers para, char *s)
{
	int		ret;
	int		len;
	int		from;
	int		s_len;
	char	*str;

	if (!s)
		return (string_type(para, "(null)"));
	len = final_str_len(para, s);
	if (!(str = malloc(len)))
		return (-1);
	s_len = ft_strlen(s);
	ft_memset(str, (' ' | para.flags.zero) * !para.flags.left | ' ', len);
	if (!para.has_prec || para.prec >= 0)
	{
		from = ft_ternary(para.has_prec, ft_min(s_len, para.prec), s_len);
		ft_strninsert(str, s, !para.flags.left * (len - from), from);
	}
	ret = write(1, str, len);
	free(str);
	return (ret);
}

static int	pointer_type(t_modifiers para, void *p)
{
	int				i;
	int				str_i;
	char			c;
	char			str[20];
	unsigned long	addr;

	if (!p)
		return (string_type(para, "0x0"));
	i = 1;
	str_i = 2;
	addr = (unsigned long)p;
	ft_strlcpy(str, "0x", 3);
	while (i <= 16 && !((addr >> 4 * (16 - i)) % 16))
		i++;
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
	else if (para.type == 'd' || para.type == 'i' || para.type == 'u' ||
		para.type == 'x' || para.type == 'X')
		return (num_type(para, va_arg(args, long long)));
	return (0);
}
