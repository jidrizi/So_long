# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 13:16:12 by jidrizi           #+#    #+#              #
#    Updated: 2024/06/15 17:02:42 by jidrizi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
LIBMLX = ./MLX42
CFLAGS = -Wall -Werror -Wextra
LIB = -lft -Llibft/ -lmlx42 -L$(LIBMLX)/build -lglfw
HEADER = -I $(LIBMLX)/include -I libft/

NAME = so_long
DEPS = so_long.h 
SRC = so_long.c so_long_pngs.c so_long_mapstuff.c 
OBJS = $(SRC:%.c=bin/%.o)

all: clean_when_debug $(NAME)

bin:
	@mkdir bin

bin/%.o : %.c | bin
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADER)

$(LIBMLX)/build/libmlx42.a:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

./libft/libft.a:
	@make -C ./libft

$(NAME): $(OBJS) $(LIBMLX)/build/libmlx42.a ./libft/libft.a $(DEPS)
	$(CC) -o $(NAME) $(LIB) $(OBJS) $(HEADER)

clean:
	@rm -fr bin/*
	@echo "washing my balls rn"

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean
	@echo "dont forget to clean your 4skin"

re: fclean all

.PHONY: all clean fclean re clean_when_debug

ifeq ($(DEBUG),1)
CFLAGS+=-g3
clean_when_debug: fclean
endif