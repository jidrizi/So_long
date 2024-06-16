/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mapstuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:01:48 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/16 21:03:54 by jidrizi          ###   ########.fr       */
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

int check_ep_duplicates(char *map_file)
{
	int p;
	int e;
	int x;

	p = 0;
	e = 0;
	x = 0;
	while (map_file[x])
	{
		if (map_file[x] == 'E')
			e++;
		if (map_file[x] == 'P')
			p++;
		x++;
	}
	if (e != 1 || p != 1)
	{
		ft_printf("Error\nDuplicate E or P\n");
		return (1);
	}
	return (0);
}

int	check_if_rectangle_map(char *map_file)
{

	int line;
	int eol; // end of line
	int first_eol;
	int first_while;
	
	line = 0;
	eol = 0;
	first_eol = 0;
	first_while = 69;
	while(map_file[line] && first_while)
	{
		if (map_file[line] == '\n')
		{
			first_eol = line;
			eol = first_eol;
			first_while = 0;
		}
		line++;
	}
	while(map_file[line])
	{
		if (map_file[line] == '\n')
		{
			if (line - eol != first_eol + 1)
					return (EXIT_FAILURE);
			eol = line;
		}
		line++;
	}
	if (map_file[line] == '\0')
	{
		if (line - eol != first_eol + 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}