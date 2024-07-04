/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:38:53 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 18:39:47 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	when_exit(char *map_file, struct s_mlx_stuff *s_stuff,
	int letter, int xy[2])
{
	if (map_file[letter] == 'E')
	{
		mlx_image_to_window(s_stuff->window, s_stuff->exit, xy[0], xy[1]);
		s_stuff->exit->instances->enabled = false;
		mlx_image_to_window(s_stuff->window, s_stuff->enemy,
			s_stuff->collectible->instances[0].x,
			s_stuff->collectible->instances[0].y);
	}
	return (EXIT_SUCCESS);
}

static int	check_if_missing_element(char *map)
{
	if (!ft_strchr(map, 'P') || !ft_strchr(map, 'E')
		|| !ft_strchr(map, 'C'))
	{
		ft_printf("Error\nMap is missing an element\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_ep_duplicates(char *map_file)
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

static char	*make_map_str(int fd)
{
	char	*tmp_map_line;
	char	*current_line;
	char	*map;

	map = NULL;
	current_line = get_next_line(fd);
	if (!current_line)
		return (NULL);
	tmp_map_line = NULL;
	while (current_line)
	{
		tmp_map_line = map;
		map = ft_strjoin(tmp_map_line, current_line);
		costum_free((void **)&current_line);
		costum_free((void **)&tmp_map_line);
		if (!map)
			return (NULL);
		current_line = get_next_line(fd);
	}
	return (map);
}

char	*get_map(char *arg1)
{
	int		fd;
	char	*map;

	fd = open(arg1, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nSomething wrong with map file\n");
		return (NULL);
	}
	map = make_map_str(fd);
	if (!map)
		return (NULL);
	close(fd);
	if (check_if_invalid_char(map) == EXIT_FAILURE)
		return (costum_free((void **)&map), NULL);
	if (check_if_missing_element(map) == EXIT_FAILURE)
		return (costum_free((void **)&map), NULL);
	if (check_ep_duplicates(map))
		return (costum_free((void **)&map), NULL);
	return (map);
}
