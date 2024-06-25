/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:29 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/25 20:59:04 by jidrizi          ###   ########.fr       */
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
	struct s_mlx_stuff	*fun_struct;
	
	fun_struct = (struct s_mlx_stuff *)param;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		mlx_image_to_window(fun_struct->window, fun_struct->player, fun_struct->player_x - 100, fun_struct->player_y);
		fun_struct->player_x = fun_struct->player_x - 100;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		mlx_image_to_window(fun_struct->window, fun_struct->player, fun_struct->player_x + 100, fun_struct->player_y);
		fun_struct->player_x = fun_struct->player_x + 100;
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		mlx_image_to_window(fun_struct->window, fun_struct->player, fun_struct->player_x, fun_struct->player_y - 100);
		fun_struct->player_y = fun_struct->player_y - 100;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		mlx_image_to_window(fun_struct->window, fun_struct->player, fun_struct->player_x, fun_struct->player_y + 100);
		fun_struct->player_y = fun_struct->player_y + 100;
	}
}
