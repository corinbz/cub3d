/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2025/01/07 13:19:13 by ccraciun         ###   ########.fr       */
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
	// printf("%s",row);
	while(row[i] && row[i] != '\n')
	{
		if(row[i] != '1' && row[i] != ' ')
		{
			// printf("%c at pos %d",row[i], i);
			return (false);
		}
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
	// printf("%s",row);
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
bool check_longer_lines(char **array, int i)
{
	int	curr_len;
	int	prev_len;
	int	nxt_len;

	curr_len = ft_strlen(array[i]);
	prev_len = ft_strlen(array[i - 1]);
	nxt_len = ft_strlen(array[i + 1]);
	
	if (curr_len > prev_len)
	{
		while(array[i][prev_len - 1] && array[i][prev_len - 1] != '\n')
		{
			if(array[i][prev_len - 1] != '1')
				return (dsp_err("long line char must be 1", false));
			prev_len++;
		}
	}
	if (curr_len > nxt_len)
	{
		while(array[i][nxt_len - 1] && array[i][prev_len - 1] != '\n')
		{
			if(array[i][nxt_len - 1] != '1')
				return (dsp_err("long line char must be 1", false));
			nxt_len++;
		}
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
		if (i == 0 || i == max_rows - 1)
		{
			if(!check_f_or_l(map_array[i]))
				return (dsp_err("First or last row contain invalid chars", false));
			i++;
			continue;
		}
		printf("%s",map_array[i]);
		if(!check_sides(map_array[i]) ||
			!check_space_neighbours(map_array[i]) ||
			!check_longer_lines(map_array, i))
			return (false);
		i++;
	}
	return (true);
}
