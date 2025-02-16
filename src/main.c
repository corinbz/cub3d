/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/16 12:15:09 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void prepare_game(t_game *game)
{

    game->mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3d", false);
    if (!game->mlx)
        print_mlx_error_and_exit();

    game->main_img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
    if (!game->main_img || (mlx_image_to_window(game->mlx, game->main_img, 0, 0) < 0))
    	print_mlx_error_and_exit();

    game->textures.wall_n = mlx_load_png(game->map->north_png_path);
    if (!game->textures.wall_n)
        print_mlx_error_and_exit();
    game->textures.wall_s = mlx_load_png(game->map->south_png_path);
    if (!game->textures.wall_s)
        print_mlx_error_and_exit();
    game->textures.wall_w = mlx_load_png(game->map->west_png_path);
    if (!game->textures.wall_w)
        print_mlx_error_and_exit();
    game->textures.wall_e = mlx_load_png(game->map->east_png_path);
    if (!game->textures.wall_e)
        print_mlx_error_and_exit();

    game->textures.wall_n_img = mlx_texture_to_image(game->mlx, game->textures.wall_n);
    if (!game->textures.wall_n_img && !mlx_resize_image(game->textures.wall_n_img, WALL_W, WALL_H))
        print_mlx_error_and_exit();
    game->textures.wall_s_img = mlx_texture_to_image(game->mlx, game->textures.wall_s);
    if (!game->textures.wall_s_img && !mlx_resize_image(game->textures.wall_s_img, WALL_W, WALL_H))
        print_mlx_error_and_exit();
    game->textures.wall_w_img = mlx_texture_to_image(game->mlx, game->textures.wall_w);
    if (!game->textures.wall_w_img && !mlx_resize_image(game->textures.wall_w_img, WALL_W, WALL_H))
        print_mlx_error_and_exit();
    game->textures.wall_e_img = mlx_texture_to_image(game->mlx, game->textures.wall_e);
    if (!game->textures.wall_e_img && !mlx_resize_image(game->textures.wall_e_img, WALL_W, WALL_H))
        print_mlx_error_and_exit();


    // int map[MAP_H][MAP_W] = {
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    // };
    // memcpy(game->data.map, map, sizeof(map));


    game->data.pos_x = game->map->player_x;
    game->data.pos_y = game->map->player_y;

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'W')
	{
		game->data.dir_x = -1;
		game->data.dir_y = 0;
		game->data.plane_x = 0;
		game->data.plane_y = 0.66;
	}

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'E')
	{
		game->data.dir_x = 1;
		game->data.dir_y = 0;
		game->data.plane_x = 0;
		game->data.plane_y = -0.66;
	}

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'S')
	{
		game->data.dir_x = 0;
		game->data.dir_y = 1;
		game->data.plane_x = 0.66;
		game->data.plane_y = 0;
	}

	if (game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] == 'N')
	{
		game->data.dir_x = 0;
		game->data.dir_y = -1;
		game->data.plane_x = -0.66;
		game->data.plane_y = 0;
	}

	game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] = '0';
}

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
	t_game	*game;
	char	*map_path;

	check_input(ac, av);
	map_path = join_strs("assets/maps/", av[1]);
	if (!map_path)
		return(dsp_err("malloc failed on join_strs in main\n"));
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return EXIT_FAILURE;
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return EXIT_FAILURE;
	if(!parse_map_file(map_path, game->map))
		return EXIT_FAILURE; //TODO print something?
	if (!valid_map(game->map))
		return EXIT_FAILURE;
	// printf("%c\n",map->player_dir);
	prepare_game(game); //TODO continue map parsing into game struct
	mlx_key_hook(game->mlx, &key_callback, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	cleanup_and_terminate_mlx(game);
	free_map(game->map); //TODO move into cleanup
	return EXIT_SUCCESS;
}

/*
int main() {
    t_game game = {0};

    prepare_and_load_textures(&game);

    mlx_key_hook(game.mlx, &key_callback, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);

    cleanup_and_terminate_mlx(&game);
    return EXIT_SUCCESS;
}

 */