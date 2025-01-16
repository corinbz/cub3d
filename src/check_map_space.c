/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:49:27 by corin             #+#    #+#             */
/*   Updated: 2025/01/16 17:20:54 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	check_addiacent_cells(char **map, int i, int j)
{
	if (map[i][j + 1])
		if (!ft_strchr(" 1", map[i][j + 1]))
			return (false);
	if (map[i][j - 1])
		if (!ft_strchr(" 1", map[i][j - 1]))
			return (false);
	if (map[i + 1])
		if (!ft_strchr(" 1", map[i + 1][j]))
			return (false);
	if (map[i - 1])
		if (!ft_strchr(" 1", map[i - 1][j]))
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
					return (dsp_err("space has invalid neighbours\n"));
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
