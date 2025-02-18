/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/18 11:25:50 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void prepare_game(t_game *game)
{

	game->mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3d", false);
	if (!game->mlx)
		print_mlx_error_clean_exit(game);
	// mlx_set_cursor_mode(game->mlx, MLX_CURSOR_CROSSHAIR);
	// mlx_set_cursor(game->mlx, MLX_CURSOR_CROSSHAIR);
	game->main_img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (!game->main_img || (mlx_image_to_window(game->mlx, game->main_img, 0, 0) < 0))
		print_mlx_error_clean_exit(game);

	game->textures.wall_n = mlx_load_png(game->map->north_png_path);
	if (!game->textures.wall_n)
		print_mlx_error_clean_exit(game);
	game->textures.wall_s = mlx_load_png(game->map->south_png_path);
	if (!game->textures.wall_s)
		print_mlx_error_clean_exit(game);
	game->textures.wall_w = mlx_load_png(game->map->west_png_path);
	if (!game->textures.wall_w)
		print_mlx_error_clean_exit(game);
	game->textures.wall_e = mlx_load_png(game->map->east_png_path);
	if (!game->textures.wall_e)
		print_mlx_error_clean_exit(game);

	game->textures.wall_n_img = mlx_texture_to_image(game->mlx, game->textures.wall_n);
	if (!game->textures.wall_n_img && !mlx_resize_image(game->textures.wall_n_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);
	game->textures.wall_s_img = mlx_texture_to_image(game->mlx, game->textures.wall_s);
	if (!game->textures.wall_s_img && !mlx_resize_image(game->textures.wall_s_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);
	game->textures.wall_w_img = mlx_texture_to_image(game->mlx, game->textures.wall_w);
	if (!game->textures.wall_w_img && !mlx_resize_image(game->textures.wall_w_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);
	game->textures.wall_e_img = mlx_texture_to_image(game->mlx, game->textures.wall_e);
	if (!game->textures.wall_e_img && !mlx_resize_image(game->textures.wall_e_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);

	game->data.pos_x = game->map->player_x;
	game->data.pos_y = game->map->player_y;

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'W')
	{
		game->data.dir_x = 1;
		game->data.dir_y = 0;
		game->data.plane_x = 0;
		game->data.plane_y = -0.66;
	}

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'E')
	{
		game->data.dir_x = -1;
		game->data.dir_y = 0;
		game->data.plane_x = 0;
		game->data.plane_y = 0.66;
	}

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'S')
	{
		game->data.dir_x = 0;
		game->data.dir_y = -1;
		game->data.plane_x = -0.66;
		game->data.plane_y = 0;
	}

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'N')
	{
		game->data.dir_x = 0;
		game->data.dir_y = 1;
		game->data.plane_x = 0.66;
		game->data.plane_y = 0;
	}
	game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] = '0';
	game->data.pos_y += 0.5;
	game->data.pos_x += 0.5;
}

static void	check_input(int ac, char **av)
{
	int	path_len;

	path_len = 0;
	if(ac != 2)
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
	if(!parse_map_file(av[1], game->map))
		return (free_map(game->map), free(game), EXIT_FAILURE); //TODO print something?
	if (!valid_map(game->map))
		return (free_map(game->map), free(game), EXIT_FAILURE);
	prepare_game(game); //TODO continue map parsing into game struct
	mlx_key_hook(game->mlx, &key_callback, game);
	mlx_cursor_hook(game->mlx, &mouse_handler, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	cleanup_and_terminate_mlx(game);
	return (EXIT_SUCCESS);
}
