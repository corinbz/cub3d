/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:35:54 by corin             #+#    #+#             */
/*   Updated: 2025/01/07 13:11:08 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdbool.h>
#include <stdio.h>

int parse_paths(char *line, t_map *map, int *line_no)
{
	strip_whitespace(line);
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
	strip_whitespace(line);
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


bool	is_valid_map_line(const char *line)
{
	const char	*allowed_chars;

	allowed_chars = "01NSE W\n";
	while (*line && ft_isspace((char)*line))
		line++;
	if (*line == '\0')
		return false;
	while(*line)
	{
		if(!ft_strchr(allowed_chars, *line))
		{
			// printf("%c not valid\n",(char)*line);
			return false;
		}
		line++;
	}
	return true;
}

void parse_map(char *line, t_map *map, int *map_ln_no)
{
	if (is_valid_map_line(line))
	{
		// printf("%s\n",line);
		map->cell_value[*map_ln_no] = ft_strdup(line);
		if (!map->cell_value[*map_ln_no])
			return (perror("strdup failed"));
		// printf("#%d--->%s",*map_ln_no, map->cell_value[*map_ln_no]);
		(*map_ln_no)++;
	}
}

int parse_map_file(char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		line_no;
	int		map_ln_no;

	line_no = 0;
	map_ln_no = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror(FILE_NO_ACCES);
	line = get_next_line(fd);
	map->cell_value = ft_calloc(500, sizeof(char*));
	while (line)
	{
		parse_map(line, map, &map_ln_no);
		parse_paths(line, map, &line_no);
		parse_colors(line, map, &line_no);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	// printf("%s",map->cell_value[0]);
	return (0);
}