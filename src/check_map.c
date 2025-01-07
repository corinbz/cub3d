/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2025/01/07 12:26:46 by ccraciun         ###   ########.fr       */
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

bool check_f_or_l(char *row)
{
	int	i;

	i = 0;
	while(row[i])
	{
		if(row[i] != '1' || row[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool check_sides(char *row)
{
	char	first;
	char	last;
	int		i;
	
	first = '\0';
	last = '\0';
	i = 0;
	printf("%s",row);
	while(row[i])
	{
		if (row[i] != ' ' && !first)
			first = row[i];
		if ((row[i] != ' ' && row[i] != '\n') && first)
			last = row[i];
		i++;
	}
	if (first != '1' || last != '1')
		return (dsp_err("First and last char must be 1", false));
	return (true);
}
bool	check_space_neighbours(char *row)
{
	int		i;
	bool	leading_space;
	i = 0;
	leading_space = true;
	while(row[i])
	{
		if (row[i] == ' ' && !leading_space)
		{
			if((row[i - 1] != '1' && row[i - 1] != ' ') &&
				row[i + 1] != '1' && row[i + 1] != ' ')
				return (dsp_err("space has invalid neighbours", false));
		}
		if (row[i] != ' ')
			leading_space = false;
		i++;
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

	map_array = map->cell_value;
	max_rows = count_rows(map_array);
	i = 0;
	j = 0;
	while(i < max_rows)
	{
		if ((i == 0 || i == max_rows - 1) && check_f_or_l(map_array[i]))
		{
			i++;
			break;
		}
		if(!check_sides(map_array[i]) || !check_space_neighbours(map_array[i]))
			return (false);
		i++;
	}
	return (true);
}
