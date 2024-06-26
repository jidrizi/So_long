/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:29 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/26 13:30:34 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*print_png(mlx_t *window, int xaxis, int yaxis, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(window, texture);
	if (!image)
		return (NULL);
	mlx_delete_texture(texture);
	if (mlx_image_to_window(window, image, xaxis, yaxis) == -1)
		return (NULL);
	return (image);
}
void move_player_hook(mlx_key_data_t keydata, void *param)
{
	struct s_mlx_stuff	*s_stuff1;
	
	s_stuff1 = (struct s_mlx_stuff *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(s_stuff1->window);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		s_stuff1->player->instances->x -= 100;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		s_stuff1->player->instances->x += 100;
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		s_stuff1->player->instances->y -= 100;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		s_stuff1->player->instances->y += 100;
	}
}
