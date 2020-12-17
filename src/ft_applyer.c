/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:14:52 by scros             #+#    #+#             */
/*   Updated: 2020/12/16 12:30:36 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len(t_modifiers para, long long num)
{
	if (para.read_as == 'l')
	{
		if (para.type == 'u')
			return (ft_ulonglen(num));
		else
			return (ft_longlen(num));
	}
	if (para.type == 'u')
		return (ft_uintlen(num));
	return (ft_intlen(num));
}

static void	nomtoa_to(t_modifiers para, long long i, char *to)
{
	if (para.read_as == 'l')
	{
		if (para.type == 'u')
			ft_ultoa_to(i, to);
		else
			ft_ltoa_to(i, to);
	}
	else
		if (para.type == 'u')
			ft_uitoa_to(i, to);
		else
			ft_itoa_to(i, to);
}

static int	final_str_len(t_modifiers para, char *s)
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

static int	prec_num_len(t_modifiers para, long long i)
{
	int prec;

	prec = 0;
	if (para.has_prec)
	{
		prec = ft_abs(para.prec);
		if (i < 0)
			prec++;
	}
	return (ft_max(num_len(para, i), prec));
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
	char	str[final_str_len(para, s)];

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

static int	num_type(t_modifiers para, long long i)
{
	int		len;
	int		shift;
	char	i_str[num_len(para, i)];
	char	str[prec_num_len(para, i) + 1];

	shift = i < 0 && (para.flags.zero) && !para.has_prec;
	if (para.has_prec && !para.prec && i == 0)
	{
		para.flags.zero = 0;
		return (string_type(para, "") + shift);
	}
	len = sizeof(str) - 1;
	str[len] = 0;
	ft_memset(&str, ft_ternary(para.has_prec, '0', ' '), len);
	nomtoa_to(para, i, i_str);
	ft_strinsert(str, i_str + (i < 0), ft_ternary(
		para.prec < 0, (i < 0), len - sizeof(i_str) + (i < 0)));
	if (para.has_prec)
		para.flags.zero = 0;
	para.has_prec = 0;
	if (shift)
	{
		write(1, "-", 1);
		if (para.min_width)
			para.min_width--;
	}
	else if (i < 0)
		str[0] = '-';
	return (string_type(para, str + shift) + shift);
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
	else if (para.type == 'd' || para.type == 'i' || para.type == 'u')
		return (num_type(para, va_arg(args, int)));
	return (0);
}
