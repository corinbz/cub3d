/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2024/12/17 13:06:24 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdbool.h>

size_t count_rows(char **cells)
{
	size_t res;

	res = 0;
	while(cells[res])
		res++;
	return (res);
}

bool valid_walls(t_map *map)
{
	bool check;
	int i;
	int j;
	size_t max_rows;
	
	max_rows = count_rows(map->cell_value);

	i = 0;
	j = 0;
	while(map->cell_value[0][j])
	{
		while(ft_isspace(map->cell_value[i][j]))
			j++;
		
	}
	
	
	return (true);
}