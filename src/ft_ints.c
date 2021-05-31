/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ints.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:14:52 by scros             #+#    #+#             */
/*   Updated: 2021/05/14 14:34:21 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_neg(t_modifiers para, long long num)
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

static int	prec_num_len(t_modifiers para, long long i)
{
	int	prec;

	prec = 0;
	if (para.has_prec)
	{
		prec = ft_abs(para.prec);
		if (para.type != 'u')
			prec += ft_strlen(get_sign(para, i));
	}
	return (ft_max(num_len(para, i), prec));
}

static int	num_comp(t_modifiers para, long long i, char *prefix, int len)
{
	char	*str;
	int		shift;
	int		ret;

	ret = 0;
	shift = ft_strlen(prefix) * (!para.has_prec && para.flags.zero);
	str = ft_calloc(1, len + 1);
	if (!str)
		return (-1);
	ft_memset(str, '0', len);
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

int	num_type(t_modifiers para, long long i)
{
	if (para.has_prec && para.flags.sign && !para.prec && !i)
	{
		para.has_prec = 0;
		return (string_type(para, "+"));
	}
	if (para.has_prec && !para.prec && !i)
		return (string_type(para, ""));
	if (!i && (para.type == 'x' || para.type == 'X'))
		para.flags.hashtag = 0;
	return (num_comp(para, i, get_sign(para, i), prec_num_len(para, i)));
}
