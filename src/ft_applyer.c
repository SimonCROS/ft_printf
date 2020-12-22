/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:14:52 by scros             #+#    #+#             */
/*   Updated: 2020/12/22 11:13:53 by scros            ###   ########lyon.fr   */
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

static char	*get_sign(t_modifiers para, long long i)
{
	if (is_neg(para, i))
		return ("-");
	if (para.flags.sign)
		return ("+");
	if (para.flags.space)
		return (" ");
	if (para.type == 'x' && para.flags.hashtag)
		return ("0x");
	if (para.type == 'X' && para.flags.hashtag)
		return ("0X");
	return ("");
}

static int	num_len(t_modifiers para, long long num)
{
	int len;
	int add;
	int prefix;

	if (para.read_as == 'l' + 1)
	{
		if (para.type == 'u')
			len = ft_ulonglonglen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_longlonglen_hex(num, 0, 0);
		else
			len = ft_longlonglen(num);
	}
	else if (para.read_as == 'l')
	{
		if (para.type == 'u')
			len = ft_ulonglen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_longlen_hex(num, 0, 0);
		else
			len = ft_longlen(num);
	}
	else if (para.read_as == 'h')
	{
		if (para.type == 'u')
			len = ft_ushortlen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_shortlen_hex(num, 0, 0);
		else
			len = ft_shortlen(num);
	}
	else if (para.read_as == 'h' + 1)
	{
		if (para.type == 'u')
			len = ft_ucharlen(num);
		else if (para.type == 'x' || para.type == 'X')
			len = ft_charlen_hex(num, 0, 0);
		else
			len = ft_charlen(num);
	}
	else if (para.type == 'u')
		len = ft_uintlen(num);
	else if (para.type == 'x' || para.type == 'X')
		len = ft_intlen_hex(num, 0, 0);
	else
		len = ft_intlen(num);
	add = !is_neg(para, num) * ft_strlen(get_sign(para, num));
	return (len + add);
}

static char	*numtoa_to(t_modifiers para, long long i, char *to)
{
	int prefix;

	prefix = *get_sign(para, i) && !(!para.has_prec && para.flags.zero);
	if (para.read_as == 'l' + 1)
	{
		if (para.type == 'u')
			return (ft_ulltoa_to(i, to));
		else if (para.type == 'x')
			return (ft_lltohex_to(i, to, prefix));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_lltohex_to(i, to, prefix)));
		else
			return (ft_lltoa_to(i, to));
	}
	if (para.read_as == 'l')
	{
		if (para.type == 'u')
			return (ft_ultoa_to(i, to));
		else if (para.type == 'x')
			return (ft_ltohex_to(i, to, prefix));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_ltohex_to(i, to, prefix)));
		else
			return (ft_ltoa_to(i, to));
	}
	if (para.read_as == 'h')
	{
		if (para.type == 'u')
			return (ft_ustoa_to(i, to));
		else if (para.type == 'x')
			return (ft_stohex_to(i, to, prefix));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_stohex_to(i, to, prefix)));
		else
			return (ft_stoa_to(i, to));
	}
	if (para.read_as == 'h' + 1)
	{
		if (para.type == 'u')
			return (ft_uctoa_to(i, to));
		else if (para.type == 'x')
			return (ft_ctohex_to(i, to, prefix));
		else if (para.type == 'X')
			return (ft_strtoupper(ft_ctohex_to(i, to, prefix)));
		else
			return (ft_ctoa_to(i, to));
	}
	if (para.type == 'u')
		return (ft_uitoa_to(i, to));
	else if (para.type == 'x')
		return (ft_itohex_to(i, to, prefix));
	else if (para.type == 'X')
		return (ft_strtoupper(ft_itohex_to(i, to, prefix)));
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
	return (ft_max(para.min, len));
}

static int	prec_num_len(t_modifiers para, long long i)
{
	int prec;

	prec = 0;
	if (para.has_prec)
	{
		prec = ft_abs(para.prec);
		if (para.type != 'u')
			prec += ft_strlen(get_sign(para, i));
	}
	return (ft_max(num_len(para, i), prec));
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

static int	string_type(t_modifiers para, char *s)
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

static int	num_type(t_modifiers para, long long i)
{
	int		len;
	int		ret;
	int		shift;
	char	*prefix;
	char	*str;

	if (para.has_prec && !para.prec && !i)
		return (string_type(para, ""));
	if (!i && (para.type == 'x' || para.type == 'X'))
		para.flags.hashtag = 0;
	ret = 0;
	prefix = get_sign(para, i);
	shift = ft_strlen(prefix) * (!para.has_prec && para.flags.zero);
	len = prec_num_len(para, i);
	if (!(str = malloc(len + 1)))
		return (-1);
	ft_memset(str, '0', len);
	str[len] = 0;
	numtoa_to(para, i, str);
	if (shift)
	{
		ret += ft_putstr_fd(prefix, 1);
		para.min = ft_max(para.min - ft_strlen(prefix), 0);
	}
	else if (*prefix || para.has_prec)
	{
		ft_strinsert(str, prefix, 0);
		para.flags.zero = 0;
	}
	para.has_prec = 0;
	ret += string_type(para, str + shift);
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
