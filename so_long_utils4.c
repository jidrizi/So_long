/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:34:46 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/29 21:25:05 by jidrizi          ###   ########.fr       */
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
