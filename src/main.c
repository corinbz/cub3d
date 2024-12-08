/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/12/08 22:53:10 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void key_callback(mlx_key_data_t keydata, void* param)
{
    t_game *game = param;

    if (keydata.action == MLX_PRESS)
        game->keyState[keydata.key] = true;
    else if (keydata.action == MLX_RELEASE)
        game->keyState[keydata.key] = false;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);
}

double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void draw_wall_slice(t_game *game, int i, double wallHeight, double sliceWidth) {
    int startY = (int)(SCREEN_H / 2 - wallHeight / 2);
    if (startY < 0) startY = 0;
    int endY = (int)(SCREEN_H / 2 + wallHeight / 2);
    if (endY >= SCREEN_H) endY = SCREEN_H - 1;

    for (int j = startY; j <= endY; j++) {
        int x = (int)(i * sliceWidth);
        for (int k = 0; k < sliceWidth; k++)
        {
            if (x + k < SCREEN_W && j < SCREEN_H)
                mlx_put_pixel(game->img, x + k, j, 0xB400B4FF);
        }
    }
}

void raycast(t_game *game) {
    double sliceWidth = (double)SCREEN_W / RAYS;
    double angleStep = game->player.fov / RAYS;

    for (int i = 0; i < RAYS; i++) {
        double rayAngle = game->player.angle - (game->player.fov / 2) + i * angleStep;
        double x = game->player.x;
        double y = game->player.y;
        double dx = cos(rayAngle);
        double dy = sin(rayAngle);

        int steps = 0;
        while (game->map[(int)floor(y)][(int)floor(x)] == 0) {
            x += dx * 0.1;
            y += dy * 0.1;
            steps++;
            if (steps > 400) break;
        }

        double distance = calculate_distance(game->player.x, game->player.y, x, y);
        double wallHeight = SCREEN_H / distance;

        draw_wall_slice(game, i, wallHeight, sliceWidth);
    }
}

bool is_player_touching_wall(t_game *game) {
    int floorX = (int)floor(game->player.x);
    int floorY = (int)floor(game->player.y);

    if (floorX < 0 || floorX >= 9 || floorY < 0 || floorY >= 10) {
        return true;
    }

    return game->map[floorY][floorX] != 0;
}

void update_player(t_game *game) {
    double speed = 0.05;
    double angularSpeed = 0.05;
    double oldX = game->player.x;
    double oldY = game->player.y;

    if (game->keyState[MLX_KEY_W]) {
        game->player.x += cos(game->player.angle) * speed;
        game->player.y += sin(game->player.angle) * speed;
    }
    if (game->keyState[MLX_KEY_S]) {
        game->player.x -= cos(game->player.angle) * speed;
        game->player.y -= sin(game->player.angle) * speed;
    }
    if (game->keyState[MLX_KEY_A]) {
        game->player.angle -= angularSpeed;
    }
    if (game->keyState[MLX_KEY_D]) {
        game->player.angle += angularSpeed;
    }

    if (game->player.angle < 0) game->player.angle += 2 * M_PI;
    if (game->player.angle >= 2 * M_PI) game->player.angle -= 2 * M_PI;

    if (is_player_touching_wall(game)) {
        game->player.x = oldX;
        game->player.y = oldY;
    }
}

void game_loop(void *param) {
    t_game *game = param;

    memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(int));

    update_player(game);
    raycast(game);
}

int main() {
    t_game game = {0};

    game.mlx = mlx_init(SCREEN_W, SCREEN_H, "Raycaster", true);
    if (!game.mlx) {
        fprintf(stderr, "Error initializing MLX: %s\n", mlx_strerror(mlx_errno));
        return EXIT_FAILURE;
    }

    game.img = mlx_new_image(game.mlx, SCREEN_W, SCREEN_H);
    if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)) {
        fprintf(stderr, "Error creating image: %s\n", mlx_strerror(mlx_errno));
        mlx_terminate(game.mlx);
        return EXIT_FAILURE;
    }

    game.player.x = 1;
    game.player.y = 1;
    game.player.angle = 1;
    game.player.fov = M_PI / 4;

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
    memcpy(game.map, map, sizeof(map));

    mlx_key_hook(game.mlx, key_callback, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);

    mlx_delete_image(game.mlx, game.img);
    mlx_terminate(game.mlx);

    return EXIT_SUCCESS;
}