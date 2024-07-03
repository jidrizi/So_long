/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:19:10 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/03 16:35:25 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	print_moves(int *moves)
{
	*moves += 1;
	ft_printf("player moves: %d\n", *moves);
}

static void	player_win(struct s_mlx_stuff *s_stuff)
{
	if (s_stuff->player->instances->x == s_stuff->exit->instances->x
		&& s_stuff->player->instances->y - 40 == s_stuff->exit->instances->y)
	{
		s_stuff->victory_ending = true;
		mlx_close_window(s_stuff->window);
	}
}

static void	check_if_touching_collectible(int player_x, int player_y,
		mlx_image_t *collectible_image)
{
	size_t	pos;

	pos = -1;
	while (collectible_image->count > ++pos)
	{
		if (player_x == collectible_image->instances[pos].x && player_y -40
			== collectible_image->instances[pos].y)
		{
			collectible_image->instances[pos].enabled = false;
		}
	}
}

static bool	check_if_all_collectibles_are_gone(mlx_image_t *collectible_image)
{
	size_t	pos;

	pos = -1;
	while (collectible_image->count > ++pos)
	{
		if (collectible_image->instances[pos].enabled == true)
		{
			return (false);
		}
	}
	return (true);
}

void	move_player(struct s_mlx_stuff *s_stuff, int direction)
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
	print_moves(&s_stuff->moves);
}
