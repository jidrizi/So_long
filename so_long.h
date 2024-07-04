/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:55 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 17:43:18 by jidrizi          ###   ########.fr       */
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
# define WALL_PATH "./png/wall.png"
# define FLOOR_PATH "./png/floor.png"
# define EXIT_PATH "./png/exit.png"
# define PLAYER_PATH "./png/playerchar2.png"
# define COLLECT_PATH "./png/Collectible.png"
# define VICTORY_PATH "./png/victory.png"
// STRUCTS
struct			s_mlx_stuff
{
	mlx_image_t		*player;
	mlx_t			*window;
	int				player_x;
	int				player_y;
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*exit;
	mlx_image_t		*collectible;
	mlx_image_t		*victory;
	bool			victory_ending;
	mlx_texture_t	*floor_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*exit_texture;
};
// ENUMS
enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// PROTOTYPES
void		costum_free(void **ptr);
mlx_image_t	*print_player(mlx_t *window, int xaxis, int yaxis, char *path);
void		put_png_in_map(char *map_file, mlx_t *window_file,
				struct s_mlx_stuff *s_file);
int			check_if_rectangle_map(char *map_file);
int			wall_frame_check(char *map_file);
int			valid_map_path_check(char *map_file, int position);
void		player_hook(mlx_key_data_t keydata, void *param);
int			check_map_elements(char *map_file);
int			check_if_going_to_walls(int player_x, int player_y,
				mlx_image_t *wall_image);
void		check_if_touching_collectible(int player_x, int player_y,
				mlx_image_t *collectible_image);
bool		check_if_all_collectibles_are_gone(
				mlx_image_t *collectible_image);
void		player_win(struct s_mlx_stuff *s_stuff);
int			get_size_first_line(char *map_file);
char		*fill_map_str(char *current_line, char *map_file,
				int fd);
int			check_if_endline_of_map_is_framed(char *map_file, int len);
void		make_image(struct s_mlx_stuff *s_stuff);
int			check_and_flag(char *map_duplicate, int x);
void		make_textures(struct s_mlx_stuff *s_stuff);
int			when_exit(char *map_file, struct s_mlx_stuff *s_stuff,
				int letter, int xy[2]);
int			when_player(char *map_file, struct s_mlx_stuff *s_stuff,
				int letter, int xy[2]);
void		print_moves(int *moves);
void		move_player(struct s_mlx_stuff *s_stuff1, int *moves,
				int direction);
void		victory_hook(mlx_key_data_t keydata, void *param);
#endif