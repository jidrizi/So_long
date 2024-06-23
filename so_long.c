/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:56:34 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/23 16:52:38 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber(char *arg1)
{
	int	len;
	int	dif;

	len = ft_strlen(arg1);
	len -= 4;
	dif = ft_strncmp(&arg1[len], ".ber", 4);
	if (dif != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	costum_free(void **ptr)
{
	if (ptr == NULL)
		return ;
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

char	*get_map(char *arg1)
{
	int		fd;
	char	*reference;
	char	*temp_reference;
	char	*line;

	fd = open(arg1, O_RDONLY);
	line = get_next_line(fd);
	reference = NULL;
	while (line)
	{
		temp_reference = reference;
		reference = ft_strjoin(temp_reference, line);
		if (!reference)
			return (costum_free((void **)&line),
				costum_free((void **)&temp_reference), NULL);
		costum_free((void **)&line);
		costum_free((void **)&temp_reference);
		line = get_next_line(fd);
	}
	if (!ft_strchr(reference, 'P') || !ft_strchr(reference, 'E')
		|| !ft_strchr(reference, 'C'))
		return (costum_free((void **)&reference), close(fd), NULL);
	if (check_ep_duplicates(reference))
		return (costum_free((void **)&reference), close(fd), NULL);
	return (close(fd), reference);
}

int	put_window(char *arg1)
{
	mlx_t	*window;
	char	*map;

	window = mlx_init(WIDTH, HEIGHT, "so_long", true);
	map = get_map(arg1);
	if (check_if_rectangle_map(map) == EXIT_FAILURE)
	{
		costum_free((void **)&map);
		ft_printf("Error\nMap is not a rectangle\n");
		return (1);
	}
	if (wall_frame_check(map) == EXIT_FAILURE)
	{
		costum_free((void **)&map);
		ft_printf("Error\nMap is not surrounded by walls\n");
		return (1);
	}
	if (valid_map_path_check(map, 0) == EXIT_FAILURE)
	{
		costum_free((void **)&map);
		ft_printf("Error\nMap has no valid path\n");
		return (1);
	}
	put_png_in_map(map, window);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop(window);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (EXIT_FAILURE);
	if (check_ber(argv[1]))
		return (EXIT_FAILURE);
	if (put_window(argv[1]) == 1)
		return (EXIT_FAILURE);
	return (0);
}

