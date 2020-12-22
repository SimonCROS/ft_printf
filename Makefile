# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 11:39:11 by scros             #+#    #+#              #
#    Updated: 2020/12/21 13:14:58 by scros            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BIN			= bin
SRC			= src
LIBFT		= libft
INC			= includes

SRCS		=	ft_applyer.c	\
				ft_parser.c		\
				ft_printf.c		\

OBJS		= $(addprefix $(BIN)/, $(SRCS:.c=.o))

NAME		= libftprintf.a
LIBFT_FILE	= $(LIBFT)/libft.a

CC			= gcc
RM			= rm -f

CFLAGS		= #-Wall -Wextra -Werror 

HEADERS		=	$(addprefix $(INC)/, ft_printf.h)

all:		$(NAME)

$(BIN)/%.o:		$(SRC)/%.c $(HEADERS)
			$(CC) $(CFLAGS) -c $< -Iincludes -Ilibft/includes -o $@

$(NAME):	compile_libft $(OBJS)
			ar rc $(NAME) $(OBJS)

compile_libft:
			@$(MAKE) -C $(LIBFT)
			@cp $(LIBFT_FILE) $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re