# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 11:39:11 by scros             #+#    #+#              #
#    Updated: 2020/12/22 14:59:34 by scros            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BIN			= bin
SRC			= src
LIBFT		= libft
INC			= includes

SRCS		=	ft_applyer.c	\
				ft_numtoa.c		\
				ft_ints.c		\
				ft_printf.c		\

OBJS		= $(addprefix $(BIN)/, $(SRCS:.c=.o))

NAME		= libftprintf.a
LIBFT_FILE	= $(LIBFT)/libft.a

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror 

HEADERS		=	$(addprefix $(INC)/, ft_printf.h)

all:		$(NAME)

$(BIN)/%.o:		$(SRC)/%.c $(HEADERS)
			$(CC) $(CFLAGS) -c $< -Iincludes -Ilibft/includes -o $@

$(NAME):	compile_lib $(OBJS)
			ar rc $(NAME) $(OBJS)

compile_lib:
			@$(MAKE) -C $(LIBFT)
			@cp $(LIBFT_FILE) $(NAME)

clean_lib:
			@$(MAKE) -C $(LIBFT) clean

fclean_lib:
			@$(MAKE) -C $(LIBFT) fclean

clean:		clean_lib
			@echo "Deleting objects...\n"
			@$(RM) $(OBJS)

fclean:		fclean_lib
			@echo "Deleting objects...\n"
			@$(RM) $(OBJS)
			@echo "Deleting $(NAME)\n"
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re compile_lib clean_lib fclean_lib