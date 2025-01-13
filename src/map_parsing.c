/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:35:54 by corin             #+#    #+#             */
/*   Updated: 2025/01/13 15:52:15 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdbool.h>
#include <stdio.h>

bool parse_paths(char *line, t_map *map)
{
	strip_whitespace(line);
	// printf("%s\n",line);
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		// printf("%s",line);
		if (map->north_png_path)
		{
			return(dsp_err("North path already exists", false));
		}
		if (!file_exists_open(line + 2))
			return(dsp_err("Cannot open file path (textures)", false));
		map->north_png_path = ft_strdup(line + 2);
		if (!map->north_png_path)
			return (dsp_err("alloc failed\n", false));
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (map->south_png_path)
			return(dsp_err("South path already exists", false));
		if (!file_exists_open(line + 2))
			return(dsp_err("Cannot open file path (textures)", false));
		map->south_png_path = ft_strdup(line + 2);
		if (!map->south_png_path)
			return (dsp_err("alloc failed\n", false));
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (map->west_png_path)
			return(dsp_err("West path already exists", false));
		if (!file_exists_open(line + 2))
			return(dsp_err("Cannot open file path (textures)", false));
		map->west_png_path = ft_strdup(line + 2);
		if (!map->west_png_path)
			return (dsp_err("alloc failed\n", false));
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (map->east_png_path)
			return (dsp_err("East path already exists", false));
		if (!file_exists_open(line + 2))
			return (dsp_err("Cannot open file path (textures)", false));
		map->east_png_path = ft_strdup(line + 2);
		if (!map->east_png_path)
			return (dsp_err("alloc failed\n", false));
	}
	return (true);
}

bool parse_colors(char *line, t_map *map)
{
	char	**color_values;
	int		i;

	i = 0;
	strip_whitespace(line);
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (map->floor_color_filled)
			return (dsp_err("Floor colors already exist", false));
		color_values = ft_split(line + 1, ',');
		if (!color_values)
			return(perror("alloc failed\n"), 1);
		while(color_values[i])
		{
			if (i > 2)
				return (dsp_err("maximum 3 color values accepted", false));
			// printf("floor color value %i is %s\n",i,color_values[i]);
			map->floor_color[i] = ft_atoi(color_values[i]);
			if (map->floor_color[i] > 255 || map->floor_color[i] < 0)
				return (dsp_err("Color value must be between 0 and 255", false));
			// printf("added floor color %i with value %i\n",i,map->floor_color[i]);
			i++;
		}
		if (i != 3)
			return (dsp_err("Floor: We need 3 color values", false));
		map->floor_color_filled = true;
		// printf("floor color filled \n");
		ft_free_2d(color_values);
	}
	i = 0;
	if (ft_strncmp(line, "C", 1) == 0)
	{
		if (map->ceiling_color_filled)
			return (dsp_err("Ceiling colors already exist", false));
		color_values = ft_split(line + 1, ',');
		if (!color_values)
			return(perror("alloc failed\n"), 1);
		while(color_values[i])
		{
			if (i > 2)
				return (dsp_err("maximum 3 color values accepted", false));
			map->ceiling_color[i] = ft_atoi(color_values[i]);
			if (map->floor_color[i] > 255 || map->floor_color[i] < 0)
				return (dsp_err("Color value must be between 0 and 255", false));
			// printf("added ceiling color %i with value %i\n",i,map->ceiling_color[i]);
			i++;
		}
		// printf("ceiling color filled\n");
		if (i != 3)
			return (dsp_err("Ceiling: We need 3 color values", false));
		map->ceiling_color_filled = true;
		ft_free_2d(color_values);
	}
	return (true);
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

bool parse_map(char *line, t_map *map, int *map_ln_no)
{
	if (is_valid_map_line(line))
	{
		//if we have no first line of the map and line is \n just skip it
		if(!map->cell_value[0] && !ft_strncmp(line,"\n",1))
			return (true);
		map->cell_value[*map_ln_no] = ft_strdup(line);
		if (!map->cell_value[*map_ln_no])
			return (perror("strdup failed"), false);
		(*map_ln_no)++;
		return (true);
		// printf("#%d--->%s",*map_ln_no, map->cell_value[*map_ln_no]);
	}
	if(map->cell_value[0])
		return (dsp_err("Invalid character found inside the map", false));
	return (true);
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
	// printf("%i\n",fd);
	line = get_next_line(fd);
	map->cell_value = ft_calloc(1024, sizeof(char*));
	while (line)
	{
		printf("%s",line);
		if (!parse_map(line, map, &line_no))
			return (free(line), 1);
		if (!parse_paths(line, map))
			return (free(line), 1);
		if (!parse_colors(line, map))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!map->ceiling_color_filled || !map->floor_color_filled ||
		!map->north_png_path || !map->south_png_path ||
		!map->west_png_path || !map->east_png_path ||
		!map->cell_value[0])
			return (dsp_err("map file is not complete", 1));
	return (0);
}
