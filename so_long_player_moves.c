/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_player_moves.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:08:19 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/30 15:31:14 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_right(struct s_mlx_stuff *s_stuff1, int *moves)
{
	if (check_if_going_to_walls(s_stuff1->player->instances->x + 100,
			s_stuff1->player->instances->y, s_stuff1->wall) == 1)
		return ;
	s_stuff1->player->instances->x += 100;
	check_if_touching_collectible(s_stuff1->player->instances->x,
		s_stuff1->player->instances->y, s_stuff1->collectible);
	if (check_if_all_collectibles_are_gone(s_stuff1->collectible) == true)
	{
		s_stuff1->exit->instances->enabled = true;
		player_win(s_stuff1);
	}
	print_moves(moves);
}

void	move_player_left(struct s_mlx_stuff *s_stuff1, int *moves)
{
	if (check_if_going_to_walls(s_stuff1->player->instances->x - 100,
			s_stuff1->player->instances->y, s_stuff1->wall) == 1)
		return ;
	s_stuff1->player->instances->x -= 100;
	check_if_touching_collectible(s_stuff1->player->instances->x,
		s_stuff1->player->instances->y, s_stuff1->collectible);
	if (check_if_all_collectibles_are_gone(s_stuff1->collectible) == true)
	{
		s_stuff1->exit->instances->enabled = true;
		player_win(s_stuff1);
	}
	print_moves(moves);
}

void	move_player_up(struct s_mlx_stuff *s_stuff1, int *moves)
{
	if (check_if_going_to_walls(s_stuff1->player->instances->x,
			s_stuff1->player->instances->y - 100, s_stuff1->wall) == 1)
		return ;
	s_stuff1->player->instances->y -= 100;
	check_if_touching_collectible(s_stuff1->player->instances->x,
		s_stuff1->player->instances->y, s_stuff1->collectible);
	if (check_if_all_collectibles_are_gone(s_stuff1->collectible) == true)
	{
		s_stuff1->exit->instances->enabled = true;
		player_win(s_stuff1);
	}
	print_moves(moves);
}

void	move_player_down(struct s_mlx_stuff *s_stuff1, int *moves)
{
	if (check_if_going_to_walls(s_stuff1->player->instances->x,
			s_stuff1->player->instances->y + 100, s_stuff1->wall) == 1)
		return ;
	s_stuff1->player->instances->y += 100;
	check_if_touching_collectible(s_stuff1->player->instances->x,
		s_stuff1->player->instances->y, s_stuff1->collectible);
	if (check_if_all_collectibles_are_gone(s_stuff1->collectible) == true)
	{
		s_stuff1->exit->instances->enabled = true;
		player_win(s_stuff1);
	}
	print_moves(moves);
}
