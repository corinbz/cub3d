/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/15 10:19:53 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_input(int ac, char **av)
{
	int	map_len;
	
	if(ac != 2)
	{
		dsp_err("Please provide a valid map path\n");
		exit(1);
	}
	map_len = ft_strlen(av[1]);
	if (ft_strncmp(av[1] + map_len - 4, ".cub", 4))
	{
		dsp_err("Please provide a valid map path\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_game	*game;
	char	*map_path;
	
	check_input(ac, av);
	map_path = join_strs("assets/maps/", av[1]);
	if (!map_path)
		return(dsp_err("malloc failed on join_strs in main\n"));
	game = ft_calloc(1, sizeof(t_game));
	map = ft_calloc(1, sizeof(t_map));
	if(parse_map_file(map_path, map))
		valid_map(map);
	// printf("%c\n",map->player_dir);
	// game->mlx = mlx_init(640,640,"Test",true);
	// mlx_key_hook(game->mlx, &ft_keyhooks, &game);
	// mlx_loop(game->mlx);
	// mlx_terminate(game->mlx);
	free_map(map);
	free(map_path);
	return (0);
}
