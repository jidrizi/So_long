/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mapstuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:01:48 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/15 19:30:57 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*map_print(char *map_file, mlx_t *window_file)
{
	int letter;
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	letter = 0;
	while (map_file[letter])
	{
		if (map_file[letter] == '1')
		{
			print_png(window_file, x, y, WALL_PATH);
			x = x + 100;
		}
		if (map_file[letter] == '0')
		{
			print_png(window_file, x, y, FLOOR_PATH);
			x = x + 100;
		}
		if (map_file[letter] == 'C')
		{
			print_png(window_file, x, y, COLLECT_PATH);
			x = x + 100;
		}
		if (map_file[letter] == 'E')
		{
			print_png(window_file, x, y, EXIT_PATH);
			x = x + 100;
		}
		if (map_file[letter] == 'P')
		{
			print_png(window_file, x, y, PLAYER_PATH);
			x = x + 100;
		}
		if (map_file[letter] == '\n')
		{
			x = 0;
			y = y + 100;
		}
		letter++;
	}
	// return ((int [2]){x, y});
	return 0;
}

int check_EPduplicates(char *map_file)
{
	int P;
	int E;
	int x;

	P = 0;
	E = 0;
	x = 0;
	while (map_file[x])
	{
		if (map_file[x] == 'E')
			E++;
		if (map_file[x] == 'P')
			P++;
		x++;
	}
	if (E != 1 || P != 1)
	{
		ft_printf("There are E or P duplicates\n");
		return (1);
	}
	return (0);
}