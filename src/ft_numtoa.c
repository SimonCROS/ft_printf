/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:59:23 by scros             #+#    #+#             */
/*   Updated: 2020/12/22 14:43:43 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_sign(t_modifiers para, long long i)
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

int			num_len_h(t_modifiers para, long long num)
{
	if (para.read_as == 'h')
	{
		if (para.type == 'u')
			return (ft_ushortlen(num));
		else if (para.type == 'x' || para.type == 'X')
			return (ft_shortlen_hex(num, 0, 0));
		else
			return (ft_shortlen(num));
	}
	else if (para.read_as == 'h' + 1)
	{
		if (para.type == 'u')
			return (ft_ucharlen(num));
		else if (para.type == 'x' || para.type == 'X')
			return (ft_charlen_hex(num, 0, 0));
		else
			return (ft_charlen(num));
	}
	else if (para.type == 'u')
		return (ft_uintlen(num));
	else if (para.type == 'x' || para.type == 'X')
		return (ft_intlen_hex(num, 0, 0));
	return (ft_intlen(num));
}

int			num_len(t_modifiers para, long long num)
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
	else
		len = num_len_h(para, num);
	add = !is_neg(para, num) * ft_strlen(get_sign(para, num));
	return (len + add);
}

static void	numtoa_to_h(t_modifiers para, long long i, char *to, int prefix)
{
	if (para.read_as == 'h')
	{
		if (para.type == 'u')
			ft_ustoa_to(i, to);
		else if (para.type == 'x' || para.type == 'X')
			ft_stohex_to(i, to, prefix);
		else
			ft_stoa_to(i, to);
	}
	else if (para.read_as == 'h' + 1)
	{
		if (para.type == 'u')
			ft_uctoa_to(i, to);
		else if (para.type == 'x' || para.type == 'X')
			ft_ctohex_to(i, to, prefix);
		else
			ft_ctoa_to(i, to);
	}
	else if (para.type == 'u')
		ft_uitoa_to(i, to);
	else if (para.type == 'x' || para.type == 'X')
		ft_itohex_to(i, to, prefix);
	else
		ft_itoa_to(i, to);
}

void		numtoa_to(t_modifiers para, long long i, char *to)
{
	int		prefix;

	prefix = *get_sign(para, i) && !(!para.has_prec && para.flags.zero);
	if (para.read_as == 'l' + 1)
	{
		if (para.type == 'u')
			ft_ulltoa_to(i, to);
		else if (para.type == 'x' || para.type == 'X')
			ft_lltohex_to(i, to, prefix);
		else
			ft_lltoa_to(i, to);
	}
	else if (para.read_as == 'l')
	{
		if (para.type == 'u')
			ft_ultoa_to(i, to);
		else if (para.type == 'x' || para.type == 'X')
			ft_ltohex_to(i, to, prefix);
		else
			ft_ltoa_to(i, to);
	}
	else
		numtoa_to_h(para, i, to, prefix);
	if (para.type == 'X')
		ft_strtoupper(to);
}
