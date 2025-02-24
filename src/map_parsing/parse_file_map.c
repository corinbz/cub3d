/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:35:54 by corin             #+#    #+#             */
/*   Updated: 2025/02/16 14:25:16 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_valid_map_line(const char *line)
{
	const char	*allowed_chars;

	allowed_chars = "01NSE W\n";
	while (*line && ft_isspace((char)*line))
		line++;
	if (*line == '\0')
		return (false);
	while (*line)
	{
		if (!ft_strchr(allowed_chars, *line))
		{
			return (false);
		}
		line++;
	}
	return (true);
}

bool	parse_map(char *line, t_map *map, int *map_ln_no)
{
	if (is_valid_map_line(line))
	{
		if (!map->cell_value[0] && !ft_strncmp(line, "\n", 1))
			return (true);
		map->cell_value[*map_ln_no] = ft_strdup(line);
		if (!map->cell_value[*map_ln_no])
			return (perror("strdup failed"), false);
		(*map_ln_no)++;
		return (true);
	}
	if (map->cell_value[0])
		return (dsp_err("Invalid character found inside the map\n"));
	return (true);
}

static bool	handle_failed_map_ln(int fd, char *line)
{
	free(line);
	line = get_next_line(fd, true);
	free(line);
	close(fd);
	return (false);
}

static bool	handle_parsing(int fd, char *line, t_map *map, int *line_no)
{
	if (!parse_map(line, map, line_no))
	{
		handle_failed_map_ln(fd, line);
		return (false);
	}
	if (!parse_paths(line, map))
	{
		handle_failed_map_ln(fd, line);
		return (false);
	}
	if (!parse_colors(line, map))
	{
		handle_failed_map_ln(fd, line);
		return (false);
	}
	return (true);
}

bool	parse_map_file(char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		line_no;

	line_no = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (dsp_err(FILE_NO_ACCES));
	count_file_lines(fd, map);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (dsp_err(FILE_NO_ACCES));
	map->cell_value = ft_calloc(map->total_ln, sizeof(char *));
	if (!map->cell_value)
		return (dsp_err("Alloc failed for map->cell_value\n"));
	line = get_next_line(fd, false);
	while (line)
	{
		if (!handle_parsing(fd, line, map, &line_no))
			return (close(fd), false);
		free(line);
		line = get_next_line(fd, false);
	}
	return (close(fd), check_map_complete(map));
}
