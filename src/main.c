/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/22 12:56:29 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void game_loop(void *param)
{
    t_game *game;
    int x;

    game = (t_game *)param;
    x = 0;
    while (x < SCREEN_W)
    {
        game->data.camera_x = 2 * x / (double)SCREEN_W - 1;
        game->data.ray_dir_x = game->data.dir_x + game->data.plane_x * game->data.camera_x;
        game->data.ray_dir_y = game->data.dir_y + game->data.plane_y * game->data.camera_x;
        game->data.map_x = (int)game->data.pos_x;
        game->data.map_y = (int)game->data.pos_y;
        if (game->data.ray_dir_x == 0)
            game->data.delta_dist_x = 1e30;
        else
            game->data.delta_dist_x = fabs(1 / game->data.ray_dir_x);
        if (game->data.ray_dir_y == 0)
            game->data.delta_dist_y = 1e30;
        else
            game->data.delta_dist_y = fabs(1 / game->data.ray_dir_y);
        if (game->data.ray_dir_x < 0)
        {
            game->data.step_x = -1;
            game->data.side_dist_x = (game->data.pos_x - game->data.map_x) * game->data.delta_dist_x;
        }
        else
        {
            game->data.step_x = 1;
            game->data.side_dist_x = (game->data.map_x + 1.0 - game->data.pos_x) * game->data.delta_dist_x;
        }
        if (game->data.ray_dir_y < 0)
        {
            game->data.step_y = -1;
            game->data.side_dist_y = (game->data.pos_y - game->data.map_y) * game->data.delta_dist_y;
        }
        else
        {
            game->data.step_y = 1;
            game->data.side_dist_y = (game->data.map_y + 1.0 - game->data.pos_y) * game->data.delta_dist_y;
        }
        while (!game->data.hit)
        {
            if (game->data.side_dist_x < game->data.side_dist_y)
            {
                game->data.side_dist_x += game->data.delta_dist_x;
                game->data.map_x += game->data.step_x;
                game->data.side = 0;
            }
            else
            {
                game->data.side_dist_y += game->data.delta_dist_y;
                game->data.map_y += game->data.step_y;
                game->data.side = 1;
            }
            if (game->data.map[game->data.map_x][game->data.map_y] > 0)
                game->data.hit = true;
        }
        x++;
    }
}

int main() {
    t_game game = {0};

    game.mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3d", false);
    if (!game.mlx) {
        printf("Error initializing MLX: %s\n", mlx_strerror(mlx_errno));
        return EXIT_FAILURE;
    }

    game.img = mlx_new_image(game.mlx, SCREEN_W, SCREEN_H);
    if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)) {
        printf("Error creating image: %s\n", mlx_strerror(mlx_errno));
        mlx_terminate(game.mlx);
        return EXIT_FAILURE;
    }

    int map[MAP_H][MAP_W] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    memcpy(game.data.map, map, sizeof(map));


    game.data.pos_x = 1;
    game.data.pos_y = 1;
    game.data.dir_x = -1;
    game.data.dir_y = 0;
    game.data.plane_x = 0;
    game.data.plane_y = 0.66;


    //
    // mlx_key_hook(game.mlx, key_callback, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    //
    mlx_delete_image(game.mlx, game.img);
    mlx_terminate(game.mlx);

    return EXIT_SUCCESS;
}