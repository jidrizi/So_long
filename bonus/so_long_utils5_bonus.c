/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils5_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:11:54 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/02 21:26:24 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	make_victory_window(void)
{
	mlx_t			*victory_window;
	mlx_texture_t	*victory_texture;
	mlx_image_t		*victory_image;

	victory_window = mlx_init(2000, 2000, "VICTORY", true);
	victory_texture = mlx_load_png(VICTORY_PATH);
	victory_image = mlx_texture_to_image(victory_window, victory_texture);
	mlx_delete_texture(victory_texture);
	mlx_image_to_window(victory_window, victory_image, 0, 0);
	mlx_key_hook(victory_window, &victory_hook, victory_window);
	mlx_loop(victory_window);
	mlx_delete_image(victory_window, victory_image);
}

void	every_other_move(struct s_mlx_stuff *s_stuff)
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

enum e_enemy_direction
{
	NONE,
	HORIZONTAL,
	VERTICAL
};

static void	move_enemy_vert(struct s_mlx_stuff *s_stuff)
{
	static int	state = UP;

	if (check_if_going_to_walls(s_stuff->enemy->instances->x,
		s_stuff->enemy->instances->y + 140, s_stuff->wall) == 0 && state != DOWN)
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
		&& mov_dir != VERTICAL  && (state == LEFT || state-- == RIGHT))
	{
		s_stuff->enemy->instances->x -= 100;
		if (mov_dir == NONE)
			mov_dir = HORIZONTAL;
	}
	else
		state = RIGHT;
	if (mov_dir == NONE)
		mov_dir = VERTICAL;
	if (mov_dir == VERTICAL)
		move_enemy_vert(s_stuff);
}
void	check_defeat_condition(void *param)
{
	struct s_mlx_stuff	*s_stuff;

	s_stuff = (struct s_mlx_stuff *)param;
	if (s_stuff->player->instances->x == s_stuff->enemy->instances->x
		&& s_stuff->player->instances->y  == s_stuff->enemy->instances->y + 40) /// do i need to add the 40 pixels to player y?
	{
		mlx_close_window(s_stuff->window);
		make_defeat_window();
	}
}
