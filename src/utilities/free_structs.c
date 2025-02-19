/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:24:01 by corin             #+#    #+#             */
/*   Updated: 2025/01/22 14:08:49 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_map(t_map *map)
{
	free(map->north_png_path);
	free(map->south_png_path);
	free(map->west_png_path);
	free(map->east_png_path);
	ft_free_2d(map->cell_value);
	free(map);
}
