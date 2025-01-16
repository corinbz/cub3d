/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:13:20 by corin             #+#    #+#             */
/*   Updated: 2025/01/16 17:18:12 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	validate_color_values(char **colors, int *values)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		if (i > 2)
			return (dsp_err("Maximum 3 color values accepted\n"));
		values[i] = ft_atoi(colors[i]);
		if (values[i] > 255 || values[i] < 0)
			return (dsp_err("Color values must be > 0 < 255\n"));
		i++;
	}
	if (i != 3)
		return (dsp_err("We need exactly 3 color values\n"));
	return (true);
}

static bool	parse_floor_color(char *line, t_map *map)
{
	char	**color_values;

	if (map->floor_color_filled)
		return (dsp_err("Floor color already exists"));
	color_values = ft_split(line + 1, ',');
	if (!color_values)
		return (dsp_err("Alloc failed for floor colors"));
	if (!validate_color_values(color_values, map->floor_color))
	{
		ft_free_2d(color_values);
		return (false);
	}
	map->floor_color_filled = true;
	ft_free_2d(color_values);
	return (true);
}

static bool	parse_ceiling_color(char *line, t_map *map)
{
	char	**color_values;

	if (map->ceiling_color_filled)
		return (dsp_err("Ceiling color already exists"));
	color_values = ft_split(line + 1, ',');
	if (!color_values)
		return (dsp_err("Alloc failed for ceiling colors"));
	if (!validate_color_values(color_values, map->ceiling_color))
	{
		ft_free_2d(color_values);
		return (false);
	}
	map->ceiling_color_filled = true;
	ft_free_2d(color_values);
	return (true);
}

bool	parse_colors(char *line, t_map *map)
{
	strip_whitespace(line);
	if (ft_strncmp(line, "F", 1) == 0)
		return (parse_floor_color(line, map));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_ceiling_color(line, map));
	return (true);
}
