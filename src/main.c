/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/15 09:25:26 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(void)
{
	t_map	*map;
	t_game	*game;
	
	game = ft_calloc(1, sizeof(t_game));
	map = ft_calloc(1, sizeof(t_map));
	if(parse_map_file("assets/maps/simple_valid.cub", map))
		valid_map(map);
	// printf("%c\n",map->player_dir);
	game->mlx = mlx_init(640,640,"Test",true);
	mlx_key_hook(game->mlx, &ft_keyhooks, &game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_map(map);
	return (0);
}
