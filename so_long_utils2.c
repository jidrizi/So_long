/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:38:48 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/29 13:56:38 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	costum_free(void **ptr)
{
	if (ptr == NULL)
		return ;
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

bool	check_if_all_collectibles_are_gone(mlx_image_t *collectible_image)
{
	size_t	pos;

	pos = -1;
	while (collectible_image->count > ++pos)
	{
		if (collectible_image->instances[pos].enabled == true)
		{
			return (false);
		}
	}
	return (true);
}

void	player_win(mlx_image_t *player, mlx_image_t *exit, mlx_t *window)
{
	if (player->instances->x == exit->instances->x && player->instances->y
		== exit->instances->y)
	{
		mlx_close_window(window);
	}
}

// int	get_size_first_line(char *map_file)
// {
// 	int	i;
// 	int	size_of_first_line;

// 	i = 0;
// 	size_of_first_line = 0;
// 	while (map_file[i])
// 	{
// 		if (map_file[i] == '\n')
// 		{
// 			size_of_first_line = i;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (size_of_first_line);
// }
