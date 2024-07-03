/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:01:32 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/03 15:41:39 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

static int	check_if_endline_of_map_is_framed(char *map_file, int len)
{
	while (map_file[--len] != '\n')
	{
		if (map_file[len] != '1')
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

static int	check_and_flag(char *map_duplicate, int x)
{
	if (map_duplicate[x] != '1')
	{
		map_duplicate[x] = '1';
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
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
