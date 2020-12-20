/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:14:52 by scros             #+#    #+#             */
/*   Updated: 2020/12/20 16:53:39 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_neg(t_modifiers para, long long num)
{
	if (ft_strindex_of("id", para.type) == -1)
		return (0);
	if (para.read_as == 'l' + 1)
		return (num < 0);
	if (para.read_as == 'l')
		return ((long)num < 0);
	if (para.read_as == 'h')
		return ((short)num < 0);
	if (para.read_as == 'h' + 1)
		return ((char)num < 0);
	return ((int)num < 0);
}

static char	get_sign(t_modifiers para, long long i)
{
	if (is_neg(para, i))
		return ('-');
	if (para.flags.sign)
		return ('+');
	if (para.flags.space)
		return (' ');
	return (0);
}

static int	num_len(t_modifiers para, long long num)
{
	int len;

	if (para.read_as == 'l' + 1)
	{
		if (para.type == 'u')
			len = ft_ulonglonglen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_longlonglen_hex(num);
		else
			len = ft_longlonglen(num);
	}
	else if (para.read_as == 'l')
	{
		if (para.type == 'u')
			len = ft_ulonglen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_longlen_hex(num);
		else
			len = ft_longlen(num);
	}
	else if (para.read_as == 'h')
	{
		if (para.type == 'u')
			len = ft_ushortlen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_shortlen_hex(num);
		else
			len = ft_shortlen(num);
	}
	else if (para.read_as == 'h' + 1)
	{
		if (para.type == 'u')
			len = ft_ucharlen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_charlen_hex(num);
		else
			len = ft_charlen(num);
	}
	else if (para.type == 'u')
		len = ft_uintlen(num);
	else if (para.type == 'x' || para.type == 'X')
		len = ft_intlen_hex(num);
	else
		len = ft_intlen(num);
	return (len + (!is_neg(para, num) && get_sign(para, num)));
}

static char	*nomtoa_to(t_modifiers para, long long i, char *to)
{
	if (para.read_as == 'l' + 1)
	{
		if (para.type == 'u')
			return (ft_ulltoa_to(i, to));
		else if (para.type == 'x')
			return (ft_lltohex_to(i, to));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_lltohex_to(i, to)));
		else
			return (ft_lltoa_to(i, to));
	}
	if (para.read_as == 'l')
	{
		if (para.type == 'u')
			return (ft_ultoa_to(i, to));
		else if (para.type == 'x')
			return (ft_ltohex_to(i, to));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_ltohex_to(i, to)));
		else
			return (ft_ltoa_to(i, to));
	}
	if (para.read_as == 'h')
	{
		if (para.type == 'u')
			return (ft_ustoa_to(i, to));
		else if (para.type == 'x')
			return (ft_stohex_to(i, to));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_stohex_to(i, to)));
		else
			return (ft_stoa_to(i, to));
	}
	if (para.read_as == 'h' + 1)
	{
		if (para.type == 'u')
			return (ft_uctoa_to(i, to));
		else if (para.type == 'x')
			return (ft_ctohex_to(i, to));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_ctohex_to(i, to)));
		else
			return (ft_ctoa_to(i, to));
	}
	if (para.type == 'u')
		return (ft_uitoa_to(i, to));
	else if (para.type == 'x')
		return (ft_itohex_to(i, to));
	else if (para.type == 'X')
		return (ft_strtoupper(ft_itohex_to(i, to)));
	return (ft_itoa_to(i, to));
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
		if (get_sign(para, i) && para.type != 'u')
			prec++;
	}
	return (ft_max(num_len(para, i), prec));
}

static int	char_type(t_modifiers para, char c)
{
	char	*str;
	int		ret;

	if (!(str = malloc(ft_max(1, para.min_width))))
		return (-1);
	ft_memset(str, ft_ternary(para.flags.left_align, ' ',
		ft_max(' ', para.flags.zero)), para.min_width);
	str[ft_ternary(para.flags.left_align, 0,
		ft_max(para.min_width - 1, 0))] = c;
	ret = write(1, str, ft_max(1, para.min_width));
	free(str);
	return (ret);
}

static int	string_type(t_modifiers para, char *s)
{
	int		ret;
	int		len;
	int		from;
	int		s_len;
	char	*str;

	len = final_str_len(para, s);
	if (!(str = malloc(len)))
		return (-1);
	if (!s)
		return (string_type(para, "(null)"));
	s_len = ft_strlen(s);
	ft_memset(str, ft_ternary(para.flags.left_align, ' ',
		ft_max(' ', para.flags.zero)), len);
	if (!para.has_prec || para.prec >= 0)
	{
		from = ft_ternary(para.has_prec, ft_min(s_len, para.prec), s_len);
		ft_strninsert(str, s, ft_ternary(para.flags.left_align, 0, len - from),
			from);
	}
	ret = write(1, str, len);
	free(str);
	return (ret);
}

static int	num_type(t_modifiers para, long long i)
{
	int		len;
	int		ret;
	int		shift;
	char	sign;
	char	*i_str;
	char	*str;

	len = prec_num_len(para, i);
	if (!(i_str = malloc(num_len(para, i))))
		return (-1);
	if (!(str = malloc(len + 1)))
	{
		free(i_str);
		return (-1);
	}
	sign = get_sign(para, i);
	shift = sign && para.flags.zero && !para.has_prec;
	if (para.has_prec && !para.prec && i == 0 && !(para.flags.zero = 0))
		return (string_type(para, ""));
	str[len] = 0;
	ft_memset(str, ft_ternary(para.has_prec, '0', ' '), len);
	ft_strinsert(str, nomtoa_to(para, i, i_str) + (sign == '-'), ft_ternary(
		para.prec < 0, !!sign, len - num_len(para, i) + !!sign));
	if (para.has_prec)
		para.flags.zero = 0;
	para.has_prec = 0;
	if (shift)
		if (write(1, &sign, 1) && para.min_width)
			para.min_width--;
	if (!shift && sign)
		str[0] = sign;
	ret = string_type(para, str + shift) + shift;
	free(i_str);
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
