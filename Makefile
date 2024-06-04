# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeFile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 13:16:12 by jidrizi           #+#    #+#              #
#    Updated: 2024/06/04 14:09:32 by jidrizi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
 
CFLAGS = -Wall -Werror -Wextra

SRC = main_test.c

DEPS = so_long.h 

HEADER = -I ./MLX42/include -I libft/

LIB = -lft -L libft/ -lmlx42 -L ./MLX42/build

LIBMLX = ./MLX42/

OBJS = $(SRC:.c=.o)


NAME = so_long

all: $(NAME)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADER)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS) libmlx
	$(CC) -o $(NAME) $(OBJS) $(LIB)

clean:
	rm -f $(OBJS)
	echo "washing my balls rn"

fclean: clean
	rm -f $(NAME)
	echo "dont forget to clean your 4skin"

re: fclean all

.PHONY: all clean fclean re