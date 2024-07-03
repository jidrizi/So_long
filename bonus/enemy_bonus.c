/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:14:40 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/03 15:15:06 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

enum e_enemy_direction
{
	NONE,
	HORIZONTAL,
	VERTICAL
};

static void	move_enemy_vert(struct s_mlx_stuff *s_stuff, int move_dir)
{
	static int	state = UP;

	if (move_dir == HORIZONTAL)
		return ;
	if (check_if_going_to_walls(s_stuff->enemy->instances->x,
			s_stuff->enemy->instances->y + 140,
			s_stuff->wall) == 0 && state != DOWN)
	{
		s_stuff->enemy->instances->y += 100;
	}
	else if (check_if_going_to_walls(s_stuff->enemy->instances->x,
			s_stuff->enemy->instances->y - 60, s_stuff->wall) == 0)
	{
		s_stuff->enemy->instances->y -= 100;
		state = DOWN;
	}
	else
		state = UP;
}

void	move_enemy(struct s_mlx_stuff *s_stuff)
{
	static int	mov_dir = NONE;
	static int	state = RIGHT;

	if (check_if_going_to_walls(s_stuff->enemy->instances->x + 100,
			s_stuff->enemy->instances->y + 40, s_stuff->wall) == 0
		&& state != LEFT && mov_dir != VERTICAL)
	{
		s_stuff->enemy->instances->x += 100;
		if (mov_dir == NONE)
			mov_dir = HORIZONTAL;
	}
	else if (check_if_going_to_walls(s_stuff->enemy->instances->x - 100,
			s_stuff->enemy->instances->y + 40, s_stuff->wall) == 0
		&& mov_dir != VERTICAL)
	{
		s_stuff->enemy->instances->x -= 100;
		state = LEFT;
		if (mov_dir == NONE)
			mov_dir = HORIZONTAL;
	}
	else
		state = RIGHT;
	if (mov_dir == NONE)
		mov_dir = VERTICAL;
	move_enemy_vert(s_stuff, mov_dir);
}
