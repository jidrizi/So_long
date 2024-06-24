/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:29 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/24 18:20:20 by jidrizi          ###   ########.fr       */
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
	if (!mlx_image_to_window(window, image, xaxis, yaxis))
		return (NULL);
	return (image);
}
void move_player_hook(mlx_key_data_t keydata,(void*) param)
{
	mlx_image_t *player1;
	
	
	while (window)
	{
		if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		{
			player1 = player;
			mlx_delete_image(window, player);
			mlx_image_to_window(window, player1, 100, 100);
		}
	}
}