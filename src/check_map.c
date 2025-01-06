/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2025/01/06 11:19:06 by corin            ###   ########.fr       */
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

bool check_f_or_l(char **map, int i, int j)
{
	while(map[i][j])
	{
		if(map[i][j] != '1' || map[i][j] != ' ')
			return (false);
		j++;
	}
	return (true);
}

bool valid_map(t_map *map)
{
	bool check;
	int i;
	int j;
	size_t max_rows;
	char **map_array;

	map_array = map->cell_value;
	max_rows = count_rows(map_array);
	i = 0;
	j = 0;
	while(map_array[i][j])
	{
		if ((i == 0 || i == max_rows) && check_f_or_l(map_array, i , j))
			i++;
		
	}
	return (true);
}