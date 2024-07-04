/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:29 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 18:42:27 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	costum_free(void **ptr)
{
	if (ptr == NULL)
		return ;
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int	get_size_first_line(char *map_file)
{
	int	size_of_first_line;

	size_of_first_line = -1;
	while (map_file[++size_of_first_line])
	{
		if (map_file[size_of_first_line] == '\n')
			break ;
	}
	return (size_of_first_line);
}

int	check_if_invalid_char(char *map_file)
{
	char	*check_if_invalid_char;

	check_if_invalid_char = ft_strtrim(map_file, "01CEP\n");
	if (check_if_invalid_char[0] != '\0')
	{
		costum_free((void **)&check_if_invalid_char);
		ft_printf("Error\nInvalid character in map\n");
		return (EXIT_FAILURE);
	}
	costum_free((void **)&check_if_invalid_char);
	return (EXIT_SUCCESS);
}
