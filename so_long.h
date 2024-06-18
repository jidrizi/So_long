/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:55 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/18 14:49:08 by jidrizi          ###   ########.fr       */
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
# define WIDTH 5120
# define HEIGHT 2880
# define WALL_PATH "/Users/jidrizi/lol/thanks_for_fish/png/wall.png"
# define FLOOR_PATH "/Users/jidrizi/lol/thanks_for_fish/png/floor.png"
# define EXIT_PATH "/Users/jidrizi/lol/thanks_for_fish/png/exit.png"
# define PLAYER_PATH "/Users/jidrizi/lol/thanks_for_fish/png/playerchar2.png"
# define COLLECT_PATH "/Users/jidrizi/lol/thanks_for_fish/png/Collectible.png"
// // ENUMS
// typedef enum e_coordinates
// {
// 	X,
// 	Y
// }			t_coordinates;

// PROTOTYPES
int		check_ber(char *arg);
void	costum_free(void **ptr);
char	*get_map(char *arg1);
int		put_window(char *arg1);
int		print_png(mlx_t *window, int xaxis, int yaxis, char *path);
void	*put_png_in_map(char *map_file, mlx_t *window_file);
int		check_ep_duplicates(char *map_file);
int		check_if_rectangle_map(char *map_file);
int		wall_frame_check(char *map_file);
#endif