/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_img_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:15:19 by corin             #+#    #+#             */
/*   Updated: 2025/01/22 14:08:40 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	handle_texture_path(const char *prefix, char **map_path, char *line)
{
	if (*map_path)
	{
		dsp_err("Path already exists");
		printf("(%s)\n", prefix);
		return (false);
	}
	if (!file_exists_open(line + 2))
		return (dsp_err("Cannot open file path (textures)\n"));
	*map_path = ft_strdup(line + 2);
	if (!*map_path)
		return (dsp_err("Memory allocation failed\n"));
	return (true);
}

bool	parse_paths(char *line, t_map *map)
{
	strip_whitespace(line);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (handle_texture_path("North", &map->north_png_path, line));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (handle_texture_path("South", &map->south_png_path, line));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (handle_texture_path("West", &map->west_png_path, line));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (handle_texture_path("East", &map->east_png_path, line));
	return (true);
}
