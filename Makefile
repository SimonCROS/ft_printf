# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 11:39:11 by scros             #+#    #+#              #
#    Updated: 2020/12/10 14:33:31 by scros            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Styles
_RESET		= \033[0m
_BOLD		= \033[1m
_UNDER		= \033[4m
_REV		= \033[7m

# Colors
_GREY		= \033[30m
_RED		= \033[31m
_GREEN		= \033[32m
_YELLOW		= \033[33m
_BLUE		= \033[34m
_PURPLE		= \033[35m
_CYAN		= \033[36m
_WHITE		= \033[37m

# Backgrounds
_IGREY		= \033[40m
_IRED		= \033[41m
_IGREEN		= \033[42m
_IYELLOW	= \033[43m
_IBLUE		= \033[44m
_IPURPLE	= \033[45m
_ICYAN		= \033[46m
_IWHITE		= \033[47m

BIN			= bin
SRC			= src
INC			= includes

CONV_SRCS	=	ft_atoi.c			\
				ft_itoa.c

LIST_SRCS	=	ft_lst_add_all.c	\
				ft_lst_clear.c		\
				ft_lst_destroy.c	\
				ft_lst_foreach.c	\
				ft_lst_get_entry.c	\
				ft_lst_is_empty.c	\
				ft_lst_last.c		\
				ft_lst_new.c		\
				ft_lst_pop.c		\
				ft_lst_set.c		\
				ft_lst_copy.c		\
				ft_lst_size.c		\
				ft_lst_map.c		\
				ft_lst_splice.c		\
				ft_lst_reduce.c		\
				ft_lst_concat.c		\
				ft_lst_shift_entry.c\
				ft_lst_get.c		\
				ft_lst_remove.c		\
				ft_lst_insert.c		\
				ft_lst_last_entry.c	\
				ft_lst_new_entry.c	\
				ft_lst_push.c		\
				ft_lst_shift.c		\
				ft_lst_slice.c		\
				ft_lst_unshift.c

MATH_SRCS	=	ft_min.c			\
				ft_max.c

MEMORY_SRCS	=	ft_bzero.c			\
				ft_calloc.c			\
				ft_memccpy.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_memset.c

PRINT_SRCS	=	ft_putchar_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_putstr_fd.c

STRING_SRCS	=	ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_isprint.c		\
				ft_split.c			\
				ft_strchr.c			\
				ft_strdup.c			\
				ft_strjoin.c		\
				ft_strlcat.c		\
				ft_strlcpy.c		\
				ft_strlen.c			\
				ft_strmapi.c		\
				ft_strncmp.c		\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_strtrim.c		\
				ft_substr.c			\
				ft_tolower.c		\
				ft_toupper.c

UTIL_SRCS	=	ft_identity.c

SRCS		=	$(addprefix convert/, $(CONV_SRCS))	\
				$(addprefix list/, $(LIST_SRCS))	\
				$(addprefix memory/, $(MEMORY_SRCS))\
				$(addprefix print/, $(PRINT_SRCS))	\
				$(addprefix string/, $(STRING_SRCS))\
				$(addprefix util/, $(UTIL_SRCS))\

OBJS		= $(addprefix $(BIN)/, $(SRCS:.c=.o))

HEADERS		= $(addprefix $(INC)/, libft.h)

NAME		= libft.a

CC			= gcc
RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror

bar			= 0
compteur	= 0
compile		= 0
count		= $(words $(SRCS))

all:		$(NAME)

ball:		bar $(NAME)
			
bar:
			$(eval bar=1)

$(BIN)/%.o: $(SRC)/%.c $(HEADERS)
			$(eval compteur=$(shell echo $$(($(compteur)+1))))
			@tabs 6; \
			if [ $(bar) -eq 0 ]; then \
				echo "$$(($(compteur)*100/$(count)))%	$(_WHITE)❖$(_RESET) $(_BLUE)Compiling source $(_GREEN)$< $(_BLUE)→ $(_YELLOW)$@$(_RESET)\c"; \
			else \
				str="\r$(_IGREEN)"; \
				if [ $$(($(compteur)*50/$(count))) -gt 0 ]; then \
					for i in $$(seq 1 $$(($(compteur)*50/$(count)))); do \
						str+=" "; \
					done; \
				fi; \
				str+="$(_IWHITE)"; \
				if [ $$((50 - ($(compteur)*50/$(count)))) -gt 0 ]; then \
					for i in $$(seq 1 $$((50 - ($(compteur)*50/$(count))))); do \
						str+=" "; \
					done; \
				fi; \
				str+="$(_RESET) $(_PURPLE)$$(($(compteur)*100/$(count)))% $(_GREEN)$< $(_BLUE)→ $(_YELLOW)$@               	"; \
				str+="$(_RESET)\c"; \
				echo "$$str"; \
			fi; \
			mkdir -p $(dir $@); \
			$(CC) $(CFLAGS) -c -o $@ $< -I $(INC); \
			if [ $(bar) -eq 0 ]; then \
				echo " $(_GREEN)✓$(_RESET)"; \
			fi;

$(NAME):	$(HEADERS) pre_compile $(OBJS) post_compile
			@ar rc $(NAME) $(OBJS)

pre_compile:
			@echo "$(_BOLD)$(_CYAN)Compiling...$(_RESET)"
			@echo "\n"

post_compile:
			@echo "\n"
			@echo "$(_RED)Finished ! $(_RESET)($(_PURPLE)$(compteur)$(_RESET) files compiled)$(_RESET)"

clean:
			@echo "🗑  $(_BOLD)$(_YELLOW)Deleting objects...$(_RESET)\n"
			@$(RM) $(OBJS)

fclean:		clean
			@echo "🗑  $(_BOLD)$(_RED)Deleting $(NAME)$(_RESET)\n"
			@$(RM) $(NAME)

re:			fclean all

bre:		fclean ball

.PHONY:		all ball bar pre_compile post_compile clean fclean re bre
