/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:29 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/24 15:24:08 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_png(mlx_t *window, int xaxis, int yaxis, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (1);
	image = mlx_texture_to_image(window, texture);
	if (!image)
		return (1);
	mlx_delete_texture(texture);
	mlx_image_to_window(window, image, xaxis, yaxis);
	return (0);
}