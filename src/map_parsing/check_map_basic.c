/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2025/02/16 10:30:47 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_rows(char **cells)
{
	int	res;

	res = 0;
	while (cells[res])
		res++;
	return (res);
}

bool	check_f_or_l(char *row)
{
	int	i;

	i = 0;
	while (row[i] && row[i] != '\n')
	{
		if (row[i] != '1' && row[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	check_sides(char *row)
{
	char	first;
	char	last;
	int		i;

	first = '\0';
	last = '\0';
	i = 0;
	while (row[i])
	{
		if (row[i] != ' ' && !first)
			first = row[i];
		if ((row[i] != ' ' && row[i] != '\n') && first)
			last = row[i];
		i++;
	}
	if (first != '1' || last != '1')
		return (dsp_err("First and last char must be 1\n"));
	return (true);
}

static bool	look_for_player(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map->cell_value[i])
	{
		while (map->cell_value[i][j])
		{
			if (ft_strchr("NSWE", map->cell_value[i][j]))
			{
				map->player_dir = map->cell_value[i][j];
				map->player_x = j;
				map->player_y = j;
				count++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (count == 1);
}

bool	valid_map(t_map *map)
{
	char	**map_array;
	int		max_rows;

	if (!map)
		return (false);
	map_array = map->cell_value;
	max_rows = count_rows(map_array);
	if (!look_for_player(map))
		return (dsp_err("Player not found or too many players\n"));
	if (!check_space_neighbours(map_array))
		return (false);
	if (!validate_rows(map_array, max_rows))
		return (false);
	return (true);
}
