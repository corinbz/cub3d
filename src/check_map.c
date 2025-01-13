/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2025/01/13 14:33:06 by ccraciun         ###   ########.fr       */
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

bool	check_addiacent_cells(char **map, int i, int j)
{
	if(map[i][j + 1])
		if (!ft_strchr(" 1",map[i][j + 1]))
			return (false);
	if (map[i][j - 1])
		if (!ft_strchr(" 1",map[i][j - 1]))
			return (false);
	if (map[i + 1])
		if (!ft_strchr(" 1",map[i + 1][j]))
			return (false);
	if (map[i - 1])
		if (!ft_strchr(" 1",map[i - 1][j]))
			return (false);
	return (true);
}

bool	check_space_neighbours(char **map)
{
	int		i;
	int		j;
	int	rows;
	bool	leading_space;
	i = 0;
	leading_space = true;
	rows = count_rows(map);
	while(map[i])
	{
		while(map[i][j])
		{
			if(map[i][j] != ' ')
			{
				leading_space = false;
				j++;
			}
			if (map[i][j] == ' ' && !leading_space)
			{
				if ((i > 0 && j > 0) && (i < rows && j < ft_strlen(map[i])))
					if(!check_addiacent_cells(map,i,j))
						return (dsp_err("space has invalid neighbours", false));
			}
			// return (dsp_err("space has invalid neighbours", false));
			j++;
		}
		leading_space = true;
		j = 0;
		i++;
	}
	return (true);
}

bool look_for_player(char **array)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while(array[i])
	{
		// printf("%s",array[i]);
		while(array[i][j])
		{
			// printf("%c",array[i][j]);
			if (ft_strchr("NSWE", array[i][j]))
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	if (count != 1)
		return (false);
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

	// printf("prev_len: %i\n",prev_len);
	// printf("curr_len: %i\n",curr_len);
	// printf("nxt_len: %i\n\n",nxt_len);
	
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
		// printf("%i%i%c\n",i,nxt_len - 1,array[i][nxt_len - 1]);
		while(array[i][nxt_len - 1] != '\n' || !array[i][nxt_len - 1])
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
	if(!look_for_player(map_array))
		return(dsp_err("Player not found or too many players", false));
	if (!check_space_neighbours(map_array))
		return(false);
	while(i < max_rows)
	{
		// printf("line %i is %s",i,map_array[i]);
		if (i == 0 || i == max_rows - 1)
		{
			if(!check_f_or_l(map_array[i]))
				return (dsp_err("First or last row contain invalid chars", false));
			i++;
			continue;
		}
		if(!check_sides(map_array[i]) ||
			!check_longer_lines(map_array, i))
			return (false);
		i++;
	}
	return (true);
}
