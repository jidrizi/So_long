# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 13:16:12 by jidrizi           #+#    #+#              #
#    Updated: 2024/07/01 20:36:13 by jidrizi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
LIBMLX = ./MLX42
CFLAGS = -Wall -Werror -Wextra
LIB = -lft -Llibft/ -lmlx42 -L$(LIBMLX)/build -lglfw
HEADER = -I $(LIBMLX)/include -I libft/

NAME = so_long
NAME_BONUS = so_long_bonus
DEPS = so_long.h 
BONUS_DEPS = so_long_bonus.h
SRC = so_long.c so_long_utils.c so_long_utils2.c so_long_utils3.c \
		so_long_mapstuff.c so_long_utils4.c
SRC_BONUS = so_long_bonus.c so_long_utils_bonus.c so_long_utils2_bonus.c \
		so_long_utils3_bonus.c so_long_mapstuff_bonus.c so_long_utils4_bonus.c
OBJS = $(SRC:%.c=bin/%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=bonus_bin/%.o)

all: clean_when_debug $(NAME)
bonus: clean_when_debug $(NAME_BONUS)

bin:
	@mkdir bin
bonus_bin:
	@mkdir bonus_bin

bin/%.o : %.c $(DEPS) | bin
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADER)

bonus_bin/%.o : %.c $(BONUS_DEPS) | bonus_bin
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADER)	

$(LIBMLX)/build/libmlx42.a:
	@git submodule update --init $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

./libft/libft.a:
	@git submodule update --init ./libft
	@make -C ./libft

$(NAME): $(LIBMLX)/build/libmlx42.a ./libft/libft.a $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIB) -ldl $(HEADER) $(CFLAGS)

$(NAME_BONUS): $(LIBMLX)/build/libmlx42.a ./libft/libft.a $(OBJS_BONUS)
	$(CC) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIB) -ldl $(HEADER) $(CFLAGS)

clean:
	@rm -fr bin/*
	@rm -fr bonus_bin/*
	@echo "washing my balls rn"

fclean: clean
	@git submodule deinit -f --all
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "dont forget to clean your 4skin"

re: fclean all

.PHONY: all clean fclean re clean_when_debug

ifeq ($(DEBUG),1)
CFLAGS+=-g3
clean_when_debug: fclean
endif