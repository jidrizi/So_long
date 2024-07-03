/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:34:46 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/03 14:13:08 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	when_exit(char *map_file, struct s_mlx_stuff *s_stuff,
	int letter, int xy[2])
{
	if (map_file[letter] == 'E')
	{
		mlx_image_to_window(s_stuff->window, s_stuff->exit, xy[0], xy[1]);
		s_stuff->exit->instances->enabled = false;
	}
	return (EXIT_SUCCESS);
}

int	when_player(char *map_file, struct s_mlx_stuff *s_stuff,
	int letter, int xy[2])
{
	if (map_file[letter] == 'P')
	{
		s_stuff->player_x = xy[0];
		s_stuff->player_y = xy[1];
	}
	return (EXIT_SUCCESS);
}

void	print_moves(int *moves)
{
	*moves += 1;
	ft_printf("player moves: %d\n", *moves);
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
