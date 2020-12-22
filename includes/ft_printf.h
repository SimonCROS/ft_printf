/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:06:43 by scros             #+#    #+#             */
/*   Updated: 2020/12/22 14:42:49 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct	s_flags
{
	char		left;
	char		sign;
	char		space;
	char		hashtag;
	char		zero;
}				t_flags;

typedef struct	s_modifiers
{
	t_flags		flags;
	int			min;
	int			has_prec;
	int			prec;
	char		read_as;
	char		type;
}				t_modifiers;

void			numtoa_to(t_modifiers para, long long i, char *to);
char			*get_sign(t_modifiers para, long long i);
int				string_type(t_modifiers para, char *s);
int				ft_applyer(t_modifiers modifiers, va_list args);
int				num_len(t_modifiers para, long long num);
int				num_type(t_modifiers para, long long i);
int				is_neg(t_modifiers para, long long num);
int				ft_printf(const char *format, ...) \
	__attribute__((format(printf,1,2)));

#endif
