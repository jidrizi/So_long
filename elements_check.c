/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:37:19 by jidrizi           #+#    #+#             */
/*   Updated: 2024/07/04 18:42:39 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_if_missing_element(char *reference)
{
	if (!ft_strchr(reference, 'P') || !ft_strchr(reference, 'E')
		|| !ft_strchr(reference, 'C'))
	{
		ft_printf("Error\nMap is missing an element\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_ep_duplicates(char *map_file)
{
	int	p;
	int	e;
	int	position;

	p = 0;
	e = 0;
	position = 0;
	while (map_file[position])
	{
		if (map_file[position] == 'E')
			e++;
		if (map_file[position] == 'P')
			p++;
		position++;
	}
	if (e != 1 || p != 1 || (e != 1 && p != 1))
	{
		ft_printf("Error\nOnly one E or P allowed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_map_elements(char *map_file)
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
	if (check_if_missing_element(map_file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_ep_duplicates(map_file))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
