# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeFile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 13:16:12 by jidrizi           #+#    #+#              #
#    Updated: 2024/06/07 15:20:30 by jidrizi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
LIBMLX = ./MLX42/
CFLAGS = -Wall -Werror -Wextra
LIB = -lft -L libft/ -lmlx42 -L $(LIBMLX)/build -lglfw
HEADER = -I $(LIBMLX)/include -I libft/

NAME = so_long
DEPS = so_long.h 
SRC = main_test.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADER)

$(LIBMLX)/build/libmlx42.a:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

./libft/libft.a:
	make -C ./libft

$(NAME): $(OBJS) $(LIBMLX)/build/libmlx42.a ./libft/libft.a
	$(CC) -o $(NAME) $(LIB) $^

clean:
	rm -f $(OBJS)
	echo "washing my balls rn"

fclean: clean
	rm -f $(NAME)
	echo "dont forget to clean your 4skin"

re: fclean all

.PHONY: all clean fclean re