/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mapstuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:01:48 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/24 15:18:38 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*put_png_in_map(char *map_file, mlx_t *window_file)
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
	return 0;
}

int check_ep_duplicates(char *map_file)
{
	int p;
	int e;
	int position;

	p = 0;
	e = 0;
	position = 0;
	while (map_file[position])
	{
		if (map_file[position] == 'E')
			e++;
		if (map_file[position] == 'P')
			p++;
		position++;
	}
	if (e != 1 || p != 1 || (e != 1 && p != 1))
	{
		ft_printf("Error\nOnly one E or P allowed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_if_rectangle_map(char *map_file)
{

	int line;
	int eol; // end of line
	int first_eol;
	
	line = 0;
	eol = 0;
	first_eol = 0;
	while(map_file[line])
	{
		if (map_file[line] == '\n')
		{
			first_eol = line;
			eol = first_eol;
			break ;
		}
		line++;
	}
	while(map_file[++line])
	{
		if (map_file[line] == '\n')
		{
			if (line - eol != first_eol + 1)
					return (EXIT_FAILURE);
			eol = line;
		}
	}
	if (map_file[line] == '\0')
	{
		if (line - eol != first_eol + 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wall_frame_check(char *map_file)
{
	int	letters;
	int	len;
	
	letters = 0;
	len = ft_strlen(map_file);
	
	while (map_file[++letters])
	{
		if (map_file[letters] == '\n' && map_file[letters + 1] != '1')
			return (EXIT_FAILURE);
		if (map_file[letters] == '\n')
			break ;
		if (map_file[letters] != '1')
			return (EXIT_FAILURE);
	}
	while (map_file[len] != '\n')
	{
		len--;
		if (map_file[len] == '\n')
			break ;
		if (map_file[len] != '1')
			return (EXIT_FAILURE);
	}
	
	while (map_file[letters++])
	{
		if (map_file[letters] == '\n')
		{
			if (map_file[letters + 1] != '1' || map_file[letters - 1] != '1')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
int valid_map_path_check(char *map_file, int position) // THE FLOOOOOD
{
	const int	first_line_size = (ft_strchr(map_file, '\n') - map_file) + 1;
	static char	*map;
	static int	i = 1;
;
	if (i)
	{
		map = ft_strdup(map_file);
		position = ft_strchr(map, 'P') - map;
		map[position] = '1';
		i = 0;
	}
	if (map[position - first_line_size] != '1')
	{
		map[position - first_line_size] = '1';
		valid_map_path_check(map, position - first_line_size);
	}
	if (map[position + first_line_size] != '1')
	{
		map[position + first_line_size] = '1';
		valid_map_path_check(map, position + first_line_size);
	}
	if (map[position - 1] != '1')
	{
		map[position -	1] = '1';
		valid_map_path_check(map, position - 1);
	}
	if (map[position + 1] != '1')
	{
		map[position + 1] = '1';
		valid_map_path_check(map, position + 1);
	}
	if (ft_strchr(map, 'C') || ft_strchr(map, 'E'))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
