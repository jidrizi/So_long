# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 13:16:12 by jidrizi           #+#    #+#              #
#    Updated: 2024/07/03 16:34:21 by jidrizi          ###   ########.fr        #
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
_SRC_BONUS = create_images_bonus.c enemy_bonus.c game_over_bonus.c get_map_bonus.c hooks_bonus.c \
			main_bonus.c map_parsing_bonus.c player_bonus.c utils_bonus.c
SRC_BONUS = $(addprefix bonus/, $(_SRC_BONUS))
OBJS = $(SRC:%.c=bin/%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=bin/%.o)

all: clean_when_debug $(NAME) $(NAME_BONUS)

bonus: $(NAME_BONUS)

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