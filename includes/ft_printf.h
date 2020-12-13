/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:06:43 by scros             #+#    #+#             */
/*   Updated: 2020/12/12 17:00:12 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct	s_flags
{
	char		left_justify;
	char		sign;
	char		space;
	char		hashtag;
	char		zero;
}				t_flags;

typedef struct	s_modifiers
{
	t_flags		*flags;
	int			min_width;
	int			precision;
	char		read_as;
	char		type;
}				t_modifiers;

int				ft_printf(const char *format, ...) \
	__attribute__((format(printf,1,2)));
int				ft_parser(const char *string, va_list args);

#endif
