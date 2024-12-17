/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/12/17 10:33:18 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

int parse_paths(char *line, t_map *map, int *line_no)
{
	if ((ft_strncmp(line, "NO", 2) == 0) && *line_no == 0)
	{
		map->north_png_path = ft_strdup(line + 2);
		if (!map->north_png_path)
			return (perror("alloc failed\n"), 1);
		(*line_no)++;
	}
	else if ((ft_strncmp(line, "SO", 2) == 0) && *line_no == 1)
	{
		map->south_png_path = ft_strdup(line + 2);
		if (!map->north_png_path)
			return (perror("alloc failed\n"), 1);
		(*line_no)++;
	}
	else if ((ft_strncmp(line, "WE", 2) == 0) && *line_no == 2)
	{
		map->west_png_path = ft_strdup(line + 2);
		if (!map->north_png_path)
			return (perror("alloc failed\n"), 1);
		(*line_no)++;
	}
	else if ((ft_strncmp(line, "EA", 2) == 0) && *line_no == 3)
	{
		map->east_png_path = ft_strdup(line + 2);
		if (!map->north_png_path)
			return (perror("alloc failed\n"), 1);
		(*line_no)++;
	}
	return (0);
}

int parse_colors(char *line, t_map *map, int *line_no)
{
	char	**color_values;
	int		i;

	i = 0;
	if ((ft_strncmp(line, "F", 1) == 0) && *line_no == 4)
	{
		color_values = ft_split(line + 1, ',');
		if (!color_values)
			return(perror("alloc failed\n"), 1);
		while(color_values[i])
		{
			map->floor_color[i] = ft_atoi(color_values[i]);
			i++;
		}
		(*line_no)++;
		ft_free_2d(color_values);
	}
	i = 0;
	if ((ft_strncmp(line, "C", 1) == 0) && *line_no == 5)
	{
		color_values = ft_split(line + 1, ',');
		if (!color_values)
			return(perror("alloc failed\n"), 1);
		while(color_values[i])
		{
			map->ceiling_color[i] = ft_atoi(color_values[i]);
			i++;
		}
		(*line_no)++;
		ft_free_2d(color_values);
	}
	return (0);
}

int read_map_file(char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		line_no;

	line_no = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror(FILE_NO_ACCES);
	line = get_next_line(fd);
	while (line)
	{
		strip_whitespace(line);
		parse_paths(line, map, &line_no);
		parse_colors(line, map, &line_no);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

int main(void)
{
	t_map	*map;
	map = ft_calloc(1, sizeof(t_map));
	read_map_file("assets/maps/simple_valid.cub", map);
	free_map(map);
	return (0);
}