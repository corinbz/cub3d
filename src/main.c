/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/16 16:51:52 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(void)
{
	t_map	*map;
	map = ft_calloc(1, sizeof(t_map));
	if(parse_map_file("assets/maps/simple_valid.cub", map))
		valid_map(map);
	// printf("%d\n",valid_map(map));
	free_map(map);
	return (0);
}
