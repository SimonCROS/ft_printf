/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:59:23 by scros             #+#    #+#             */
/*   Updated: 2020/12/22 13:32:48 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_neg(t_modifiers para, long long num)
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

char	*get_sign(t_modifiers para, long long i)
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

int		num_len(t_modifiers para, long long num)
{
	int len;
	int add;

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

char	*numtoa_to(t_modifiers para, long long i, char *to)
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
