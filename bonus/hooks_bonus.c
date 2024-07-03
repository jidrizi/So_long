/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:11:24 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/03 16:35:16 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	display_moves(struct s_mlx_stuff *s_stuff, int direction)
{
	static mlx_image_t	*image_of_moves;
	char				*itoa_moves;

	if (image_of_moves != NULL)
		image_of_moves->instances->enabled = false;
	mlx_delete_image(s_stuff->window, image_of_moves);
	if (direction == UP)
		move_player(s_stuff, UP);
	if (direction == DOWN)
		move_player(s_stuff, DOWN);
	if (direction == LEFT)
		move_player(s_stuff, LEFT);
	if (direction == RIGHT)
		move_player(s_stuff, RIGHT);
	itoa_moves = ft_itoa(s_stuff->moves);
	image_of_moves = mlx_put_string(s_stuff->window, (const char *)itoa_moves,
			80, 0);
	if (itoa_moves)
		free (itoa_moves);
	move_enemy(s_stuff);
}

int	check_if_going_to_walls(int player_x, int player_y, mlx_image_t *wall_image)
{
	size_t	pos;

	pos = -1;
	while (wall_image->count > ++pos)
	{
		if (player_x == wall_image->instances[pos].x && player_y - 40
			== wall_image->instances[pos].y)
		{
			return (1);
		}
	}
	return (0);
}

static void	every_other_move(struct s_mlx_stuff *s_stuff)
{
	s_stuff->animation->instances->x = s_stuff->player->instances->x;
	s_stuff->animation->instances->y = s_stuff->player->instances->y - 40;
	mlx_set_instance_depth(s_stuff->animation->instances,
		s_stuff->player->instances->z);
	if (s_stuff->moves % 2 != 0)
	{
		s_stuff->player->instances->enabled = false;
		s_stuff->animation->instances->enabled = true;
	}
	else
	{
		s_stuff->player->instances->enabled = true;
		s_stuff->animation->instances->enabled = false;
	}
}

void	player_hook(mlx_key_data_t keydata, void *param)
{
	struct s_mlx_stuff	*s_stuff;

	s_stuff = (struct s_mlx_stuff *)param;
	s_stuff->victory_ending = false;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(s_stuff->window);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		display_moves(s_stuff, RIGHT);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		display_moves(s_stuff, LEFT);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		display_moves(s_stuff, UP);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		display_moves(s_stuff, DOWN);
	mlx_set_instance_depth(s_stuff->enemy->instances,
		s_stuff->player->instances->z);
	every_other_move(s_stuff);
}
