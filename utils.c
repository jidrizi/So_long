/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:03:42 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 21:56:40 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	costum_free(void **ptr)
{
	if (ptr == NULL)
		return ;
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int	check_if_endline_of_map_is_framed(char *map_file, int len)
{
	if (map_file[len - 1] == '\n')
		len--;
	while (map_file[--len] != '\n')
	{
		if (map_file[len] != '1')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*fill_map_str(char *current_line, char *map_file, int fd)
{
	char	*temp_line;

	temp_line = NULL;
	while (current_line)
	{
		temp_line = map_file;
		map_file = ft_strjoin(temp_line, current_line);
		costum_free((void **)&current_line);
		costum_free((void **)&temp_line);
		if (!map_file)
			return (NULL);
		current_line = get_next_line(fd);
	}
	return (map_file);
}

int	check_and_flag(char *map_duplicate, int x)
{
	if (map_duplicate[x] != '1')
	{
		map_duplicate[x] = '1';
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
