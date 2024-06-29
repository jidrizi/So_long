/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:56:34 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/29 20:31:06 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber(char *arg1)
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

char	*get_map(char *arg1)
{
	int		fd;
	char	*reference;
	char	*current_line;

	fd = open(arg1, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nSomething wrong with map file\n");
		return (NULL);
	}
	reference = NULL;
	current_line = get_next_line(fd);
	reference = create_proper_reference(current_line, reference, fd);
	if (check_if_missing_element(reference) == EXIT_FAILURE)
		return (costum_free((void **)&reference), close (fd), NULL);
	if (check_ep_duplicates(reference))
		return (costum_free((void **)&reference), close(fd), NULL);
	return (close(fd), reference);
}

int	put_window(char *arg1, struct s_mlx_stuff *s_stuff)
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
	mlx_key_hook(s_stuff->window, &move_player_hook, (void *)s_stuff);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop(s_stuff->window);
	mlx_terminate(s_stuff->window);
	return (0);
}

void	victory_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window((mlx_t *)param);
	}
}

int	main(int argc, char *argv[])
{
	mlx_texture_t		*victory_texture;
	mlx_image_t			*victory_image;
	mlx_t				*victory_window;
	struct s_mlx_stuff	*s_stuff;

	s_stuff = ft_calloc(sizeof(struct s_mlx_stuff), 1);
	if (argc != 2)
		return (EXIT_FAILURE);
	if (check_ber(argv[1]))
		return (EXIT_FAILURE);
	if (put_window(argv[1], s_stuff) == 1)
		return (EXIT_FAILURE);
	if (s_stuff->escape == true)
		return (0);
	victory_window = mlx_init(2000, 2000, "VICTORY", true);
	victory_texture = mlx_load_png(VICTORY_PATH);
	victory_image = mlx_texture_to_image(victory_window, victory_texture);
	mlx_delete_texture(victory_texture);
	mlx_image_to_window(victory_window, victory_image, 0, 0);
	mlx_key_hook(victory_window, &victory_hook, victory_window);
	mlx_loop(victory_window);
	mlx_delete_image(victory_window, victory_image);
	return (0);
}
