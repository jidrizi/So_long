/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:07:11 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/03 18:43:44 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	victory_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window((mlx_t *)param);
	}
}

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

void	make_victory_window(void)
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

void	check_defeat_condition(void *param)
{
	struct s_mlx_stuff	*s_stuff;

	s_stuff = (struct s_mlx_stuff *)param;
	if (s_stuff->player->instances->x == s_stuff->enemy->instances->x
		&& s_stuff->player->instances->y == s_stuff->enemy->instances->y + 40)
	{
		mlx_close_window(s_stuff->window);
	}
}
