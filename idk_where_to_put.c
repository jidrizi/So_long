/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_game_mechanics.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:29 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 17:28:56 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_if_all_collectibles_are_gone(mlx_image_t *collectible_image)
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

void	victory_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window((mlx_t *)param);
	}
}


