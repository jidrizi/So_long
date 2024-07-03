/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:06:02 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/03 16:12:25 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	make_textures(struct s_mlx_stuff *s_stuff)
{
	s_stuff->enemy_texture = mlx_load_png(ENEMY_PATH);
	s_stuff->animation_texture = mlx_load_png(ANIMATION_PATH);
	s_stuff->wall_texture = mlx_load_png(WALL_PATH);
	s_stuff->collectible_texture = mlx_load_png(COLLECT_PATH);
	s_stuff->exit_texture = mlx_load_png(EXIT_PATH);
	s_stuff->floor_texture = mlx_load_png(FLOOR_PATH);
}

void	make_image(struct s_mlx_stuff *s_stuff)
{
	s_stuff->wall = mlx_texture_to_image(s_stuff->window,
			s_stuff->wall_texture);
	mlx_delete_texture(s_stuff->wall_texture);
	s_stuff->collectible = mlx_texture_to_image(s_stuff->window,
			s_stuff->collectible_texture);
	mlx_delete_texture(s_stuff->collectible_texture);
	s_stuff->exit = mlx_texture_to_image(s_stuff->window,
			s_stuff->exit_texture);
	mlx_delete_texture(s_stuff->exit_texture);
	s_stuff->floor = mlx_texture_to_image(s_stuff->window,
			s_stuff->floor_texture);
	mlx_delete_texture(s_stuff->floor_texture);
	s_stuff->animation = mlx_texture_to_image(s_stuff->window,
			s_stuff->animation_texture);
	mlx_delete_texture(s_stuff->animation_texture);
	mlx_image_to_window(s_stuff->window, s_stuff->animation, 0, 0);
	s_stuff->animation->instances->enabled = true;
	s_stuff->enemy = mlx_texture_to_image(s_stuff->window,
			s_stuff->enemy_texture);
	mlx_delete_texture(s_stuff->enemy_texture);
}

static int	when_player(char *map_file, struct s_mlx_stuff *s_stuff,
	int letter, int xy[2])
{
	if (map_file[letter] == 'P')
	{
		s_stuff->player_x = xy[0];
		s_stuff->player_y = xy[1] + 40;
	}
	return (EXIT_SUCCESS);
}

static mlx_image_t	*print_player(mlx_t *window, int x, int y, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(window, texture);
	if (!image)
		return (NULL);
	mlx_delete_texture(texture);
	if (mlx_image_to_window(window, image, x, y) == -1)
		return (NULL);
	return (image);
}

//i[0] = the x axis and i[1] = the y axis
void	put_png_in_map(char *map_file, mlx_t *window_file,
		struct s_mlx_stuff *s_stuff)
{
	int	letter;
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	letter = -1;
	while (map_file[++letter])
	{
		mlx_image_to_window(window_file, s_stuff->floor, i[0], i[1]);
		if (map_file[letter] == '1')
			mlx_image_to_window(window_file, s_stuff->wall, i[0], i[1]);
		if (map_file[letter] == 'C')
			mlx_image_to_window(window_file, s_stuff->collectible, i[0], i[1]);
		when_exit(map_file, s_stuff, letter, i);
		when_player(map_file, s_stuff, letter, i);
		i[0] = i[0] + 100;
		if (map_file[letter] == '\n')
		{
			i[0] = 0;
			i[1] = i[1] + 100;
		}
	}
	s_stuff->player = print_player(window_file, s_stuff->player_x,
			s_stuff->player_y, PLAYER_PATH);
	mlx_put_string(window_file, "MOVES:", 0, 0);
}
