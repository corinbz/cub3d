/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2025/01/07 10:29:47 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdbool.h>

int count_rows(char **cells)
{
	int res;

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
	// bool check;
	int		i;
	int		j;
	int		max_rows;
	char	**map_array;
	char	first;
	char	last;

	map_array = map->cell_value;
	char first = '\0';
	char last = '\0';
	max_rows = count_rows(map_array);
	i = 0;
	j = 0;
	while(i < max_rows)
	{
		while(map_array[i][j])
		{
			if ((i == 0 || i == max_rows - 1) && check_f_or_l(map_array, i, j))
				break;
			printf("%c",map_array[i][j]);
			if (map_array[i][j] != ' ' && !first)
				first = map_array[i][j];
			if (map_array[i][j] != ' ' && first)
				first = map_array[i][j];
				
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
}