/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:10:28 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 18:45:05 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_hook(mlx_key_data_t keydata, void *param)
{
	struct s_mlx_stuff	*s_stuff1;
	static int			moves = 0;

	s_stuff1 = (struct s_mlx_stuff *)param;
	s_stuff1->victory_ending = false;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(s_stuff1->window);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(s_stuff1, &moves, RIGHT);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(s_stuff1, &moves, LEFT);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(s_stuff1, &moves, UP);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(s_stuff1, &moves, DOWN);
}

void	player_win(struct s_mlx_stuff *s_stuff)
{
	if (s_stuff->player->instances->x == s_stuff->exit->instances->x
		&& s_stuff->player->instances->y == s_stuff->exit->instances->y)
	{
		s_stuff->victory_ending = true;
		mlx_close_window(s_stuff->window);
	}
}

mlx_image_t	*print_player(mlx_t *window, int xaxis, int yaxis, char *path)
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

void	move_player(struct s_mlx_stuff *s_stuff, int *moves, int direction)
{
	int	player_x;
	int	player_y;

	player_x = s_stuff->player->instances->x;
	player_y = s_stuff->player->instances->y;
	if (direction == UP)
		player_y -= 100;
	if (direction == DOWN)
		player_y += 100;
	if (direction == LEFT)
		player_x -= 100;
	if (direction == RIGHT)
		player_x += 100;
	if (check_if_going_to_walls(player_x, player_y, s_stuff->wall) == 1)
		return ;
	s_stuff->player->instances->x = player_x;
	s_stuff->player->instances->y = player_y;
	check_if_touching_collectible(player_x, player_y, s_stuff->collectible);
	if (check_if_all_collectibles_are_gone(s_stuff->collectible) == true)
	{
		s_stuff->exit->instances->enabled = true;
		player_win(s_stuff);
	}
	print_moves(moves);
}

//no where else to put it
void	print_moves(int *moves)
{
	*moves += 1;
	ft_printf("player moves: %d\n", *moves);
}
