/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:55 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/29 20:02:59 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// EXTERNAL LIB
# include <fcntl.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// LOCAL LIBRARIES
# include "MLX42/MLX42.h"
# include "libft.h"

// MACROS
// # define WIDTH 5120
// # define HEIGHT 2880
# define WALL_PATH "/Users/jidrizi/lol/thanks_for_fish/png/wall.png"
# define FLOOR_PATH "/Users/jidrizi/lol/thanks_for_fish/png/floor.png"
# define EXIT_PATH "/Users/jidrizi/lol/thanks_for_fish/png/exit.png"
# define PLAYER_PATH "/Users/jidrizi/lol/thanks_for_fish/png/playerchar2.png"
# define COLLECT_PATH "/Users/jidrizi/lol/thanks_for_fish/png/Collectible.png"
# define VICTORY_PATH "/Users/jidrizi/lol/thanks_for_fish/png/victory.png"
// STRUCTS
struct			s_mlx_stuff
{
	mlx_image_t	*player;
	mlx_t		*window;
	int			player_x;
	int			player_y;
	mlx_image_t	*wall;
	mlx_image_t	*exit;
	mlx_image_t	*collectible;
	mlx_image_t	*victory;
	bool		escape;
};
// PROTOTYPES
int				check_ber(char *arg);
void			costum_free(void **ptr);
char			*get_map(char *arg1);
int				put_window(char *arg1, struct s_mlx_stuff *s_stuff);
mlx_image_t		*print_png(mlx_t *window, int xaxis, int yaxis, char *path);
mlx_image_t		*put_png_in_map(char *map_file, mlx_t *window_file,
					struct s_mlx_stuff *s_file);
int				check_ep_duplicates(char *map_file);
int				check_if_rectangle_map(char *map_file);
int				wall_frame_check(char *map_file);
int				valid_map_path_check(char *map_file, int position);
void			move_player_hook(mlx_key_data_t keydata, void *param);
int				check_if_going_to_walls(int player_x, int player_y,
					mlx_image_t *wall_image);
int				*finder_of_width_height(char *map_file);
void			check_if_touching_collectible(int player_x, int player_y,
					mlx_image_t *collectible_image);
bool			check_if_all_collectibles_are_gone(
					mlx_image_t *collectible_image);
void			player_win(mlx_image_t *player, mlx_image_t *exit,
					mlx_t *window);
int				get_size_first_line(char *map_file);
int				check_if_missing_element(char *reference);
char			*create_proper_reference(char *current_line, char *reference,
					int fd);
int				check_if_endline_of_map_is_framed(char *map_file, int len);
void			make_image(struct s_mlx_stuff *s_stuff,
					mlx_texture_t *wall_texture,
					mlx_texture_t *collectible_texture,
					mlx_texture_t *exit_texture);
int				check_and_flag(char *map_duplicate, int x);
#endif