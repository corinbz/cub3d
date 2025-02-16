/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:31:34 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/16 14:26:12 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	file_exists_open(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (true);
	}
	return (false);
}

void	count_file_lines(int fd, t_map *map)
{
	char	*line;
	int		res;

	res = 0;
	line = get_next_line(fd, false);
	while (line)
	{
		free(line);
		line = get_next_line(fd, false);
		res++;
	}
	map->total_ln = res;
	close(fd);
}

bool	check_map_complete(t_map *map)
{
	if (!map->ceiling_color_filled || !map->floor_color_filled
		|| !map->north_png_path || !map->south_png_path
		|| !map->west_png_path || !map->east_png_path
		|| !map->cell_value[0])
	{
		return (dsp_err("map file is not complete\n"));
	}
	return (true);
}
