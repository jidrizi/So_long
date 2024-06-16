/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:55 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/15 19:31:06 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// EXTERNAL LIB
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <fcntl.h>

// LOCAL LIBRARIES
# include "libft.h"
# include "MLX42/MLX42.h"

// MACROS
# define WIDTH 256
# define HEIGHT 256
# define WALL_PATH "/Users/jidrizi/lol/thanks_for_fish/png/wall.png"
# define FLOOR_PATH "/Users/jidrizi/lol/thanks_for_fish/png/floor.png"
# define EXIT_PATH "/Users/jidrizi/lol/thanks_for_fish/png/exit.png"
# define PLAYER_PATH "/Users/jidrizi/lol/thanks_for_fish/png/playerchar2.png"
# define COLLECT_PATH "/Users/jidrizi/lol/thanks_for_fish/png/Collectible.png"
// ENUMS
typedef enum e_coordinates
{
	X,
	Y
}			t_coordinates;

int		check_ber(char *arg);
void	costum_free(void **ptr);
char	*get_map(char *arg1);
int		put_window(char *arg1);
int		print_png(mlx_t *window, int xaxis, int yaxis, char *path);
void	*map_print(char *map_file, mlx_t *window_file);
int		check_EPduplicates(char *map_file);

#endif