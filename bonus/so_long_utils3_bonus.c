/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils3_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:04:19 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/02 19:12:01 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*create_proper_reference(char *current_line, char *reference, int fd)
{
	char	*temp_reference;

	temp_reference = NULL;
	while (current_line)
	{
		temp_reference = reference;
		reference = ft_strjoin(temp_reference, current_line);
		costum_free((void **)&current_line);
		costum_free((void **)&temp_reference);
		if (!reference)
			return (NULL);
		current_line = get_next_line(fd);
	}
	return (reference);
}

int	check_if_endline_of_map_is_framed(char *map_file, int len)
{
	while (map_file[--len] != '\n')
	{
		if (map_file[len] != '1')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	make_image(struct s_mlx_stuff *s_stuff)
{
	s_stuff->wall = mlx_texture_to_image(s_stuff->window,
			s_stuff->wall_texture);
	mlx_delete_texture(s_stuff->wall_texture);
	s_stuff->collectible = mlx_texture_to_image(s_stuff->window,
			s_stuff->collectible_texture);
	mlx_delete_texture(s_stuff->collectible_texture);
	s_stuff->exit = mlx_texture_to_image(s_stuff->window,
			s_stuff->exit_texture);
	mlx_delete_texture(s_stuff->exit_texture);
	s_stuff->floor = mlx_texture_to_image(s_stuff->window,
			s_stuff->floor_texture);
	mlx_delete_texture(s_stuff->floor_texture);
	s_stuff->animation = mlx_texture_to_image(s_stuff->window,
			s_stuff->animation_texture);
	mlx_delete_texture(s_stuff->animation_texture);
	mlx_image_to_window(s_stuff->window, s_stuff->animation, 0, 0);
	s_stuff->animation->instances->enabled = true;
	s_stuff->enemy = mlx_texture_to_image(s_stuff->window,
			s_stuff->enemy_texture);
	mlx_delete_texture(s_stuff->enemy_texture);
	mlx_image_to_window(s_stuff->window, s_stuff->enemy, 600, 600);
}

int	check_and_flag(char *map_duplicate, int x)
{
	if (map_duplicate[x] != '1')
	{
		map_duplicate[x] = '1';
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	make_textures(struct s_mlx_stuff *s_stuff)
{
	s_stuff->enemy_texture = mlx_load_png(ENEMY_PATH);
	s_stuff->animation_texture = mlx_load_png(ANIMATION_PATH);
	s_stuff->wall_texture = mlx_load_png(WALL_PATH);
	s_stuff->collectible_texture = mlx_load_png(COLLECT_PATH);
	s_stuff->exit_texture = mlx_load_png(EXIT_PATH);
	s_stuff->floor_texture = mlx_load_png(FLOOR_PATH);
}
