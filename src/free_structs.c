/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:24:01 by corin             #+#    #+#             */
/*   Updated: 2024/12/17 10:27:47 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void free_map(t_map *map)
{
	free(map->north_png_path);
	free(map->south_png_path);
	free(map->west_png_path);
	free(map->east_png_path);
	free(map);
}