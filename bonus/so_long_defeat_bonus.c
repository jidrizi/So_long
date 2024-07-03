/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_defeat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:07:11 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/02 21:28:43 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	make_defeat_window(void)
{
	mlx_t			*defeat_window;
	mlx_texture_t	*defeat_texture;
	mlx_image_t		*defeat_image;

	defeat_window = mlx_init(2000, 2000, "DEFEAT", true);
	defeat_texture = mlx_load_png(DEFEAT_PATH);
	defeat_image = mlx_texture_to_image(defeat_window, defeat_texture);
	mlx_delete_texture(defeat_texture);
	mlx_image_to_window(defeat_window, defeat_image, 0, 0);
	mlx_key_hook(defeat_window, &victory_hook, defeat_window);
	mlx_loop(defeat_window);
	mlx_delete_image(defeat_window, defeat_image);
}
