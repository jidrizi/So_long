/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:56:34 by jidrizi           #+#    #+#             */
/*   Updated: 2024/06/12 15:46:46 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key(mlx_key_data_t keydata, void* param)
{
	mlx_t *window;

	window = (mlx_t*)param;
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
	{
		mlx_texture_t* t_player = mlx_load_png("/Users/jidrizi/lol/playerchar2.png");
		mlx_image_t* i_player = mlx_texture_to_image(window, t_player);
		mlx_image_to_window(window,i_player, 300, 300);
	}
}

int	check_ber(char *arg)
{
	int	len;
	int	dif;

	len = ft_strlen(arg);
	len -= 4;
	dif = ft_strncmp(&arg[len], ".ber", 4);
	if (dif != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	read_map(char *arg)
{
	int fd;

	fd = open(arg, O_RDONLY);
	get_next_line(fd);
	close(fd);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	mlx_t*	window;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (check_ber(argv[1]))
		return (EXIT_FAILURE);
	window = mlx_init(WIDTH, HEIGHT, "thanksforfish", true);
	if(!window)
		printf("this window dont work men");
	// mlx_texture_t* t_collectible = mlx_load_png("../Untitled.png");
	// mlx_texture_t* t_wall = mlx_load_png("/Users/jidrizi/lol/wall.png");
	// if (!t_collectible || !t_wall)
	//     printf("this texture dont work men");
	// mlx_image_t* i_collectible = mlx_texture_to_image(window, t_collectible);
	// mlx_image_t* i_wall = mlx_texture_to_image(window, t_wall);
	// if (!i_collectible || !i_wall) 
	//     printf("this image dont work men");
	// mlx_image_to_window(window, i_wall, 0, 0);
	// mlx_image_to_window(window,i_collectible, 500, 500);
	// mlx_resize_image(i_collectible, 50, 50);
	// mlx_key_hook(window, &key_test, (void *)window);
	mlx_loop(window);
	return 0;
}
