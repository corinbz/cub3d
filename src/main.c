/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/18 12:21:49 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_input(int ac, char **av)
{
	int	path_len;

	path_len = 0;
	if (ac != 2)
	{
		dsp_err("Please provide a valid map path\n");
		exit(1);
	}
	path_len = ft_strlen(av[1]);
	if (ft_strncmp(av[1] + path_len - 4, ".cub", 4))
	{
		dsp_err("Please provide a valid map path. Wrong extension\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_game	*game;

	check_input(ac, av);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (EXIT_FAILURE);
	if (!parse_map_file(av[1], game->map))
		return (free_map(game->map), free(game), EXIT_FAILURE);
	if (!valid_map(game->map))
		return (free_map(game->map), free(game), EXIT_FAILURE);
	prepare_game(game);
	mlx_key_hook(game->mlx, &key_callback, game);
	mlx_cursor_hook(game->mlx, &mouse_handler, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	cleanup_and_terminate_mlx(game);
	return (EXIT_SUCCESS);
}
