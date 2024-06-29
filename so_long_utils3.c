/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:04:19 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/29 19:59:43 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*create_proper_reference(char *current_line, char *reference, int fd)
{
	char	*temp_reference;

	temp_reference = NULL;
	while (current_line)
	{
		temp_reference = reference;
		reference = ft_strjoin(temp_reference, current_line);
		if (!reference)
			return (costum_free((void **)&current_line),
				costum_free((void **)&temp_reference), NULL);
		costum_free((void **)&current_line);
		costum_free((void **)&temp_reference);
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

void	make_image(struct s_mlx_stuff *s_stuff, mlx_texture_t *wall_texture,
			mlx_texture_t *collectible_texture, mlx_texture_t *exit_texture)
{
	s_stuff->wall = mlx_texture_to_image(s_stuff->window, wall_texture);
	s_stuff->collectible = mlx_texture_to_image(s_stuff->window,
			collectible_texture);
	s_stuff->exit = mlx_texture_to_image(s_stuff->window, exit_texture);
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
