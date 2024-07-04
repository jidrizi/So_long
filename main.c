/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:56:34 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 17:37:25 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_ber(char *arg1)
{
	int	len;
	int	dif;

	len = ft_strlen(arg1);
	len -= 4;
	if (len < 0)
	{
		ft_printf("Error\nFile is not a .ber file\n");
		return (EXIT_FAILURE);
	}
	dif = ft_strncmp(&arg1[len], ".ber", 4);
	if (dif != 0)
	{
		ft_printf("Error\nFile is not a .ber file\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	*get_map(char *arg1)
{
	int		fd;
	char	*map;
	char	*current_line;


	fd = open(arg1, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nSomething wrong with map file\n"), NULL);
	map = NULL;
	current_line = get_next_line(fd);
	map = fill_map_str(current_line, map, fd);
	if (!map)
		return (close(fd), NULL);
	if (check_map_elements(map) == EXIT_FAILURE)
		return (costum_free((void **)&map), close(fd), NULL);
	return (close(fd), map);
}
static int	*finder_of_width_height(char *map_file)
{
	int	width;
	int	pos;
	int	height;

	width = 0;
	height = 0;
	while (map_file[width] != '\n')
		width++;
	height++;
	pos = width;
	while (map_file[pos])
	{
		if (map_file[pos] == '\n')
			height++;
		pos++;
	}
	height = height * 100;
	width = width * 100;
	return ((int [2]){width, height});
}

static int	put_window(char *arg1, struct s_mlx_stuff *s_stuff)
{
	char	*map;
	int		*for_window;

	map = get_map(arg1);
	if (!map)
		return (1);
	if (check_if_rectangle_map(map) == EXIT_FAILURE)
		return (costum_free((void **)&map), 1);
	if (wall_frame_check(map) == EXIT_FAILURE)
		return (costum_free((void **)&map), 1);
	if (valid_map_path_check(map, 0) == EXIT_FAILURE)
	{
		ft_printf("Error\nMap has no valid path\n");
		return (costum_free((void **)&map), 1);
	}
	for_window = finder_of_width_height(map);
	s_stuff->window = mlx_init(for_window[0], for_window[1], "so_long", true);
	make_textures(s_stuff);
	make_image(s_stuff);
	put_png_in_map(map, s_stuff->window, s_stuff);
	mlx_key_hook(s_stuff->window, &player_hook, (void *)s_stuff);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop(s_stuff->window);
	mlx_terminate(s_stuff->window);
	return (costum_free((void **)&map), 0);
}



int	main(int argc, char *argv[])
{
	mlx_texture_t		*victory_texture;
	mlx_image_t			*victory_image;
	mlx_t				*victory_window;
	struct s_mlx_stuff	*s_stuff;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (check_ber(argv[1]))
		return (EXIT_FAILURE);
	s_stuff = ft_calloc(sizeof(struct s_mlx_stuff), 1);
	if (!s_stuff)
		return (EXIT_FAILURE);
	if (put_window(argv[1], s_stuff) == 1)
		return (EXIT_FAILURE);
	if (s_stuff->victory_ending == false)
		return ((costum_free((void **)&s_stuff), 0));
	victory_window = mlx_init(2000, 2000, "VICTORY", true);
	victory_texture = mlx_load_png(VICTORY_PATH);
	victory_image = mlx_texture_to_image(victory_window, victory_texture);
	mlx_delete_texture(victory_texture);
	mlx_image_to_window(victory_window, victory_image, 0, 0);
	mlx_key_hook(victory_window, &victory_hook, victory_window);
	mlx_loop(victory_window);
	mlx_delete_image(victory_window, victory_image);
	return (costum_free((void **)&s_stuff), 0);
}
