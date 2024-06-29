/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mapstuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:01:48 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/29 15:03:40 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*put_png_in_map(char *map_file, mlx_t *window_file,
				struct s_mlx_stuff *s_stuff)
{
	int				letter;
	int				x;
	int				y;
	mlx_image_t		*player;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*exit_texture;

	x = 0;
	y = 0;
	letter = 0;
	wall_texture = mlx_load_png(WALL_PATH);
	collectible_texture = mlx_load_png(COLLECT_PATH);
	exit_texture = mlx_load_png(EXIT_PATH);
	s_stuff->wall = mlx_texture_to_image(window_file, wall_texture);
	s_stuff->collectible = mlx_texture_to_image(window_file,
			collectible_texture);
	s_stuff->exit = mlx_texture_to_image(window_file, exit_texture);
	mlx_delete_texture(wall_texture);
	mlx_delete_texture(collectible_texture);
	mlx_delete_texture(exit_texture);
	while (map_file[letter])
	{
		if (map_file[letter] == '1')
		{
			mlx_image_to_window(window_file, s_stuff->wall, x, y);
			x = x + 100;
		}
		if (map_file[letter] == '0')
		{
			print_png(window_file, x, y, FLOOR_PATH);
			x = x + 100;
		}
		if (map_file[letter] == 'C')
		{
			print_png(window_file, x, y, FLOOR_PATH);
			mlx_image_to_window(window_file, s_stuff->collectible, x, y);
			x = x + 100;
		}
		if (map_file[letter] == 'E')
		{
			print_png(window_file, x, y, FLOOR_PATH);
			mlx_image_to_window(window_file, s_stuff->exit, x, y);
			s_stuff->exit->instances->enabled = false;
			x = x + 100;
		}
		if (map_file[letter] == 'P')
		{
			print_png(window_file, x, y, FLOOR_PATH);
			s_stuff->player_x = x;
			s_stuff->player_y = y;
			x = x + 100;
		}
		if (map_file[letter] == '\n')
		{
			x = 0;
			y = y + 100;
		}
		letter++;
	}
	player = print_png(window_file, s_stuff->player_x, s_stuff->player_y,
			PLAYER_PATH);
	return (player);
}

int	check_ep_duplicates(char *map_file)
{
	int	p;
	int	e;
	int	position;

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

//prev_eol = previous end of line and pos = position
int	check_if_rectangle_map(char *map_file)
{
	int	pos;
	int	prev_eol;
	const int	size_of_first_line = get_size_first_line(map_file);

	pos = size_of_first_line;
	prev_eol = size_of_first_line;
	while (map_file[++pos])
	{
		if (map_file[pos] == '\n')
		{
			if (pos - prev_eol != size_of_first_line + 1)
				return (EXIT_FAILURE);
			prev_eol = pos;
		}
	}
	if (map_file[pos] == '\0')
	{
		if (pos - prev_eol != size_of_first_line + 1)
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

//FLOOD
int	valid_map_path_check(char *map_file, int position)
{
	const int	first_line_size = (ft_strchr(map_file, '\n') - map_file) + 1;
	static char	*map_duplicate;
	static int	i = 1;

	if (i)
	{
		map_duplicate = ft_strdup(map_file);
		position = ft_strchr(map_duplicate, 'P') - map_duplicate;
		map_duplicate[position] = '1';
		i = 0;
	}
	if (map_duplicate[position - first_line_size] != '1')
	{
		map_duplicate[position - first_line_size] = '1';
		valid_map_path_check(map_duplicate, position - first_line_size);
	}
	if (map_duplicate[position + first_line_size] != '1')
	{
		map_duplicate[position + first_line_size] = '1';
		valid_map_path_check(map_duplicate, position + first_line_size);
	}
	if (map_duplicate[position - 1] != '1')
	{
		map_duplicate[position - 1] = '1';
		valid_map_path_check(map_duplicate, position - 1);
	}
	if (map_duplicate[position + 1] != '1')
	{
		map_duplicate[position + 1] = '1';
		valid_map_path_check(map_duplicate, position + 1);
	}
	if (ft_strchr(map_duplicate, 'C') || ft_strchr(map_duplicate, 'E'))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
