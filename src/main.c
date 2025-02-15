/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/15 09:24:46 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void prepare_and_load_textures(t_game *game)
{
    game->mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3d", false);
    if (!game->mlx)
        print_mlx_error_and_exit();

    game->main_img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
    if (!game->main_img || (mlx_image_to_window(game->mlx, game->main_img, 0, 0) < 0))
        print_mlx_error_and_exit();

    game->textures.wall_n = mlx_load_png("textures/wall_n.png");
    if (!game->textures.wall_n)
        print_mlx_error_and_exit();
    game->textures.wall_s = mlx_load_png("textures/wall_s.png");
    if (!game->textures.wall_s)
        print_mlx_error_and_exit();
    game->textures.wall_w = mlx_load_png("textures/wall_w.png");
    if (!game->textures.wall_w)
        print_mlx_error_and_exit();
    game->textures.wall_e = mlx_load_png("textures/wall_e.png");
    if (!game->textures.wall_e)
        print_mlx_error_and_exit();

    game->textures.wall_n_img = mlx_texture_to_image(game->mlx, game->textures.wall_n);
    if (!game->textures.wall_n_img)
        print_mlx_error_and_exit();
    game->textures.wall_s_img = mlx_texture_to_image(game->mlx, game->textures.wall_s);
    if (!game->textures.wall_s_img)
        print_mlx_error_and_exit();
    game->textures.wall_w_img = mlx_texture_to_image(game->mlx, game->textures.wall_w);
    if (!game->textures.wall_w_img)
        print_mlx_error_and_exit();
    game->textures.wall_e_img = mlx_texture_to_image(game->mlx, game->textures.wall_e);
    if (!game->textures.wall_e_img)
        print_mlx_error_and_exit();


    int map[MAP_H][MAP_W] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    memcpy(game->data.map, map, sizeof(map));


    game->data.pos_x = 2;
    game->data.pos_y = 2;
    game->data.dir_x = -1;
    game->data.dir_y = 0;
    game->data.plane_x = 0;
    game->data.plane_y = 0.66;
}


int main() {
    t_game game = {0};

    prepare_and_load_textures(&game);

    mlx_key_hook(game.mlx, &key_callback, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);

    cleanup_and_terminate_mlx(&game);
    return EXIT_SUCCESS;
}
