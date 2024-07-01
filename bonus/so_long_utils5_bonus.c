/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils5_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:11:54 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/01 22:28:24 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
void make_victory_window(void)
{
	mlx_t			*victory_window;
	mlx_texture_t	*victory_texture;
	mlx_image_t		*victory_image;
	
	victory_window = mlx_init(2000, 2000, "VICTORY", true);
	victory_texture = mlx_load_png(VICTORY_PATH);
	victory_image = mlx_texture_to_image(victory_window, victory_texture);
	mlx_delete_texture(victory_texture);
	mlx_image_to_window(victory_window, victory_image, 0, 0);
	mlx_key_hook(victory_window, &victory_hook, victory_window);
	mlx_loop(victory_window);
	mlx_delete_image(victory_window, victory_image);
}