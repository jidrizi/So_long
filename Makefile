# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 13:16:12 by jidrizi           #+#    #+#              #
#    Updated: 2024/07/01 22:14:37 by jidrizi          ###   ########.fr        #
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
BONUS_DEPS = bonus/so_long_bonus.h
SRC = so_long.c so_long_utils.c so_long_utils2.c so_long_utils3.c \
		so_long_mapstuff.c so_long_utils4.c
SRC_BONUS = bonus/so_long_bonus.c bonus/so_long_utils_bonus.c bonus/so_long_utils2_bonus.c bonus/so_long_utils3_bonus.c\
			bonus/so_long_mapstuff_bonus.c bonus/so_long_utils4_bonus.c bonus/so_long_utils5_bonus.c
OBJS = $(SRC:%.c=bin/%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=bin/%.o)

all: clean_when_debug $(NAME)
all_bonus: clean_when_debug $(NAME_BONUS)

bin/bonus:
	@mkdir -p bin/bonus

bin/%.o : %.c $(DEPS) | bin/bonus
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADER)

$(LIBMLX)/build/libmlx42.a:
	@git submodule update --init $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

./libft/libft.a:
	@git submodule update --init ./libft
	@make -C ./libft

$(NAME): $(LIBMLX)/build/libmlx42.a ./libft/libft.a $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIB) -ldl $(HEADER) $(CFLAGS)

$(NAME_BONUS): $(LIBMLX)/build/libmlx42.a ./libft/libft.a $(OBJS_BONUS) $(BONUS_DEPS)
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