/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:49:39 by corin             #+#    #+#             */
/*   Updated: 2025/01/16 17:20:59 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	check_line_length(char *line, int max_len, int len)
{
	while (line[len - 1] && line[len - 1] != '\n')
	{
		if (line[len - 1] != '1')
			return (dsp_err("long line char must be 1\n"));
		len++;
		if (len > max_len)
			break ;
	}
	return (true);
}

static bool	check_longer_lines(char **array, int i)
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
			return (dsp_err("First or last row contain invalid chars\n"));
		return (true);
	}
	if (!check_sides(map_array[i]) || !check_longer_lines(map_array, i))
		return (false);
	return (true);
}

bool	validate_rows(char **map_array, int max_rows)
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
