/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:57 by corin             #+#    #+#             */
/*   Updated: 2025/01/16 15:34:25 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static bool	check_single_row(char **map, int i, int rows)
{
	int		j;
	bool	leading_space;

	j = 0;
	leading_space = true;
	while (map[i][j])
	{
		if (map[i][j] != ' ')
			leading_space = false;
		if (map[i][j] == ' ' && !leading_space)
			if ((i > 0 && j > 0) && (i < rows && j < ft_strlen(map[i])))
				if (!check_addiacent_cells(map, i, j))
					return (dsp_err("space has invalid neighbours", false));
		j++;
	}
	return (true);
}

bool	check_space_neighbours(char **map)
{
	int		i;
	int		rows;

	i = 0;
	rows = count_rows(map);
	while (map[i])
	{
		if (!check_single_row(map, i, rows))
			return (false);
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
		while(array[i][j])
		{
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

static bool	check_line_length(char *line, int max_len, int len)
{
	while (line[len - 1] && line[len - 1] != '\n')
	{
		if (line[len - 1] != '1')
			return (dsp_err("long line char must be 1", false));
		len++;
		if (len > max_len)
			break ;
	}
	return (true);
}

bool	check_longer_lines(char **array, int i)
{
	int	curr_len;
	int	prev_len;
	int	nxt_len;

	curr_len = ft_strlen(array[i]);
	prev_len = ft_strlen(array[i - 1]);
	nxt_len = ft_strlen(array[i + 1]);
	if (curr_len > prev_len)
		if (!check_line_length(array[i], curr_len, prev_len))
			return (false);
	if (curr_len > nxt_len)
		if (!check_line_length(array[i], curr_len, nxt_len))
			return (false);
	return (true);
}

static bool	check_row(char **map_array, int i, int max_rows)
{
	if (i == 0 || i == max_rows - 1)
	{
		if (!check_f_or_l(map_array[i]))
			return (dsp_err("First or last row contain invalid chars", false));
		return (true);
	}
	if (!check_sides(map_array[i]) || !check_longer_lines(map_array, i))
		return (false);
	return (true);
}

static bool	validate_rows(char **map_array, int max_rows)
{
	int	i;

	i = 0;
	while (i < max_rows)
	{
		if (!check_row(map_array, i, max_rows))
			return (false);
		i++;
	}
	return (true);
}

bool	valid_map(t_map *map)
{
	char	**map_array;
	int		max_rows;

	map_array = map->cell_value;
	max_rows = count_rows(map_array);
	if (!look_for_player(map_array))
		return (dsp_err("Player not found or too many players", false));
	if (!check_space_neighbours(map_array))
		return (false);
	if (!validate_rows(map_array, max_rows))
		return (false);
	return (true);
}
