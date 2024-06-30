/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:29 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/30 22:19:53 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*print_png(mlx_t *window, int xaxis, int yaxis, char *path)
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
	if (mlx_image_to_window(window, image, xaxis, yaxis) == -1)
		return (NULL);
	return (image);
}

void	move_player_hook(mlx_key_data_t keydata, void *param)
{
	struct s_mlx_stuff	*s_stuff1;
	static int			moves = 0;
	char				*window_moves;
	static mlx_image_t	*move_image = NULL;
	
	window_moves = NULL;
	s_stuff1 = (struct s_mlx_stuff *)param;
	s_stuff1->victory_ending = false;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(s_stuff1->window);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (move_image != NULL)
			move_image->instances->enabled = false;
		mlx_delete_image(s_stuff1->window, move_image);
		move_player(s_stuff1, &moves, RIGHT);
		window_moves = ft_itoa(moves);
		move_image = mlx_put_string(s_stuff1->window,(const char *)window_moves,
				80, 0);
		if (window_moves)
			free(window_moves);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (move_image != NULL)
			move_image->instances->enabled = false;
		mlx_delete_image(s_stuff1->window, move_image);
		move_player(s_stuff1, &moves, LEFT);
		window_moves = ft_itoa(moves);
		move_image = mlx_put_string(s_stuff1->window,(const char *)window_moves,
				80, 0);
		if (window_moves)
			free(window_moves);
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (move_image != NULL)
			move_image->instances->enabled = false;
		mlx_delete_image(s_stuff1->window, move_image);
		move_player(s_stuff1, &moves, UP);
		window_moves = ft_itoa(moves);
		move_image = mlx_put_string(s_stuff1->window,(const char *)window_moves,
				80, 0);
		if (window_moves)
			free(window_moves);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (move_image != NULL)
			move_image->instances->enabled = false;
		mlx_delete_image(s_stuff1->window, move_image);
		move_player(s_stuff1, &moves, DOWN);
		window_moves = ft_itoa(moves);
		move_image = mlx_put_string(s_stuff1->window,(const char *)window_moves,
				80, 0);
		if (window_moves)
			free(window_moves);
	}
}

int	check_if_going_to_walls(int player_x, int player_y, mlx_image_t *wall_image)
{
	size_t	pos;

	pos = -1;
	while (wall_image->count > ++pos)
	{
		if (player_x == wall_image->instances[pos].x && player_y
			== wall_image->instances[pos].y)
		{
			return (1);
		}
	}
	return (0);
}

int	*finder_of_width_height(char *map_file)
{
	int	width;
	int	pos;
	int	height;

	width = 0;
	height = 0;
	while (map_file[width] != '\n')
		width++;
	height++;
	pos = width;
	while (map_file[pos])
	{
		if (map_file[pos] == '\n')
			height++;
		pos++;
	}
	height = height * 100;
	width = width * 100;
	return ((int [2]){width, height});
}

void	check_if_touching_collectible(int player_x, int player_y,
		mlx_image_t *collectible_image)
{
	size_t	pos;

	pos = -1;
	while (collectible_image->count > ++pos)
	{
		if (player_x == collectible_image->instances[pos].x && player_y
			== collectible_image->instances[pos].y)
		{
			collectible_image->instances[pos].enabled = false;
		}
	}
}
