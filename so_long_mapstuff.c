/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mapstuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:01:48 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/30 21:15:52 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_png_in_map(char *map_file, mlx_t *window_file,
		struct s_mlx_stuff *s_stuff)
{
	int	letter;
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	letter = -1;
	while (map_file[++letter])
	{
		mlx_image_to_window(window_file, s_stuff->floor, i[0], i[1]);
		if (map_file[letter] == '1')
			mlx_image_to_window(window_file, s_stuff->wall, i[0], i[1]);
		if (map_file[letter] == 'C')
			mlx_image_to_window(window_file, s_stuff->collectible, i[0], i[1]);
		when_exit(map_file, s_stuff, letter, i);
		when_player(map_file, s_stuff, letter, i);
		i[0] = i[0] + 100;
		if (map_file[letter] == '\n')
		{
			i[0] = 0;
			i[1] = i[1] + 100;
		}
	}
	s_stuff->player = print_png(window_file, s_stuff->player_x,
			s_stuff->player_y, PLAYER_PATH);
	mlx_put_string(window_file,"MOVES:", 0, 0);
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

// prev_eol = previous end of line and pos = position
int	check_if_rectangle_map(char *map_file)
{
	int			pos;
	int			prev_eol;
	const int	size_of_first_line = get_size_first_line(map_file);

	pos = size_of_first_line;
	prev_eol = size_of_first_line;
	while (map_file[++pos])
	{
		if (map_file[pos] == '\n')
		{
			if (pos - prev_eol != size_of_first_line + 1)
				return (ft_printf("Error\nMap is not a rectangle\n"),
					EXIT_FAILURE);
			prev_eol = pos;
		}
	}
	if (map_file[pos] == '\0')
	{
		if (pos - prev_eol != size_of_first_line + 1)
			return (ft_printf("Error\nMap is not a rectangle\n"),
				EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wall_frame_check(char *map_file)
{
	int	letters;
	int	len;

	letters = 0;
	len = ft_strlen(map_file);
	while (map_file[letters] && map_file[++letters] != '\n')
		if (map_file[letters] != '1')
			return (ft_printf("Error\nMap has no wall frame\n"), EXIT_FAILURE);
	if (map_file[++letters] != '1')
		return (ft_printf("Error\nMap has no wall frame\n"), EXIT_FAILURE);
	while (map_file[letters++])
	{
		if (map_file[letters] == '\n')
		{
			if (map_file[letters + 1] != '1' || map_file[letters - 1] != '1')
				return (ft_printf("Error\nMap has no wall frame\n"), 1);
		}
	}
	if (check_if_endline_of_map_is_framed(map_file, len) == EXIT_FAILURE)
		return (ft_printf("Error\nMap has no wall frame\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// FLOOD
int	valid_map_path_check(char *map_file, int position)
{
	const int	first_line_size = (ft_strchr(map_file, '\n') - map_file) + 1;
	static char	*map_duplicate = NULL;
	const int	player_pos = ft_strchr(map_file, 'P') - map_file;

	if (map_duplicate == NULL)
	{
		map_duplicate = ft_strdup(map_file);
		position = ft_strchr(map_duplicate, 'P') - map_duplicate;
		map_duplicate[position] = '1';
	}
	if (!check_and_flag(map_duplicate, position - first_line_size))
		valid_map_path_check(map_duplicate, position - first_line_size);
	if (!check_and_flag(map_duplicate, position + first_line_size))
		valid_map_path_check(map_duplicate, position + first_line_size);
	if (!check_and_flag(map_duplicate, position - 1))
		valid_map_path_check(map_duplicate, position - 1);
	if (!check_and_flag(map_duplicate, position + 1))
		valid_map_path_check(map_duplicate, position + 1);
	if ((ft_strchr(map_duplicate, 'C') || ft_strchr(map_duplicate, 'E'))
		&& position == player_pos)
		return (costum_free((void **)&map_duplicate), EXIT_FAILURE);
	if (position == player_pos)
		return (costum_free((void **)&map_duplicate), EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
