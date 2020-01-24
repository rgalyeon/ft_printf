# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/20 20:07:49 by rgalyeon          #+#    #+#              #
#    Updated: 2020/01/23 20:41:00 by rgalyeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra
NAME = libftprintf.a

LIBFT_SRC = srcs/conv/ft_atoi.c \
            srcs/math/ft_int_len.c \
            srcs/char/ft_isdigit.c \
            srcs/char/ft_toupper.c \
            srcs/memory/ft_memalloc.c \
            srcs/memory/ft_memset.c \
            srcs/memory/ft_bzero.c \
            srcs/memory/ft_memcpy.c \
            srcs/string/ft_str_upper.c \
            srcs/string/ft_strcmp.c \
            srcs/string/ft_strlen.c \
            srcs/string/ft_strchr.c \
            srcs/string/ft_strdup.c \
            srcs/string/ft_strcpy.c \
            srcs/string/ft_strreverse.c \
            srcs/sort/ft_swap.c \
            srcs/struct/vector/ft_vec_init.c \
            srcs/struct/vector/ft_vec_push.c \
            srcs/struct/vector/ft_vec_string_push.c

SRC = srcs/ft_printf.c \
      srcs/ft_vfprintf.c \
      srcs/parse_placeholder.c \
      srcs/processing_types/processing_c.c \
      srcs/processing_types/processing_di.c \
      srcs/processing_types/processing_p.c \
      srcs/processing_types/processing_s.c \
      srcs/processing_types/processing_u.c \
      srcs/processing_types/processing_x.c \
      srcs/processing_types/processing_f.c \
      srcs/processing_types.c \
      srcs/utils/ft_itoa_base.c \
      srcs/utils/bignum.c \
      srcs/utils/ftoa.c \
      srcs/utils.c \
      $(addprefix libft/, $(LIBFT_SRC))




OBJ = $(SRC:.c=.o)

HEADERS = includes/ft_printf.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $@ $(OBJ)

%.o: %.c $(HEADERS)
	@gcc $(FLAGS) -I libft/includes -I includes/ -c $< -o $@

clean:
	@-rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@-rm -f $(NAME)
	@make fclean -C libft

test: all
	make -C pft
	./pft/test

re: fclean all
