/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/12/17 12:19:17 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(void)
{
	t_map	*map;
	map = ft_calloc(1, sizeof(t_map));
	parse_map_file("assets/maps/simple_valid.cub", map);
	valid_walls(map);
	free_map(map);
	return (0);
}