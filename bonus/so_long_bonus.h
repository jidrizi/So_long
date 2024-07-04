/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:55 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 18:39:32 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

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
# define WALL_PATH "./png/wall.png"
# define FLOOR_PATH "./png/floor.png"
# define EXIT_PATH "./png/exit.png"
# define PLAYER_PATH "./png/playerchar2.png"
# define ANIMATION_PATH "./png/animation.png"
# define COLLECT_PATH "./png/Collectible.png"
# define VICTORY_PATH "./png/victory.png"
# define ENEMY_PATH "./png/Enemy.png"
# define DEFEAT_PATH "./png/defeat.png"
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
	int				moves;
	mlx_texture_t	*animation_texture;
	mlx_image_t		*animation;
	mlx_image_t		*enemy;
	mlx_texture_t	*enemy_texture;
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
void			make_textures(struct s_mlx_stuff *s_stuff);
void			make_image(struct s_mlx_stuff *s_stuff);
void			put_png_in_map(char *map_file, mlx_t *window_file,
					struct s_mlx_stuff *s_file);
void			move_enemy(struct s_mlx_stuff *s_stuff);
void			make_victory_window(void);
void			player_hook(mlx_key_data_t keydata, void *param);
int				check_if_going_to_walls(int player_x, int player_y,
					mlx_image_t *wall_image);
void			move_player(struct s_mlx_stuff *s_stuff1, int direction);
int				check_if_rectangle_map(char *map_file);
int				wall_frame_check(char *map_file);
int				valid_map_path_check(char *map_file, int position);
void			costum_free(void **ptr);
char			*get_map(char *arg1);
int				get_size_first_line(char *map_file);
int				when_exit(char *map_file, struct s_mlx_stuff *s_stuff,
					int letter, int xy[2]);
void			check_defeat_condition(void *param);
void			make_defeat_window(void);
int				check_if_invalid_char(char *map_file);
#endif