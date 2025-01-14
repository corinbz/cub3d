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

void draw_wall_slice(t_game *game, int i, double wallHeight, double sliceWidth, double wallX) {
    int startY = (int)(SCREEN_H / 2 - wallHeight / 2);
    int endY = (int)(SCREEN_H / 2 + wallHeight / 2);
    
    // Draw ceiling
    for (int y = 0; y < startY; y++) {
        int x = (int)(i * sliceWidth);
        for (int k = 0; k < sliceWidth; k++) {
            if (x + k < SCREEN_W && y < SCREEN_H) {
                int texX = ((x + k) * game->ceiling_texture.width / SCREEN_W) % game->ceiling_texture.width;
                int texY = (y * game->ceiling_texture.height / startY) % game->ceiling_texture.height;
                uint32_t color = game->ceiling_texture.pixels[texY * game->ceiling_texture.width + texX];
                // MLX42 expects RGBA format (each component 8 bits)
                uint8_t b = (color >> 0) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t r = (color >> 16) & 0xFF;
                uint8_t a = (color >> 24) & 0xFF;
                mlx_put_pixel(game->img, x + k, y, (r << 24) | (g << 16) | (b << 8) | a);
            }
        }
    }

    // Draw wall
    if (startY < 0) startY = 0;
    if (endY >= SCREEN_H) endY = SCREEN_H - 1;

    for (int y = startY; y <= endY; y++) {
        int x = (int)(i * sliceWidth);
        double texY = (y - startY) / (double)(endY - startY);
        int texX = (int)(wallX * game->wall_texture.width) % game->wall_texture.width;
        int texYCoord = (int)(texY * game->wall_texture.height);
        
        uint32_t color = game->wall_texture.pixels[texYCoord * game->wall_texture.width + texX];
        // MLX42 expects RGBA format (each component 8 bits)
        uint8_t b = (color >> 0) & 0xFF;
        uint8_t g = (color >> 8) & 0xFF;
        uint8_t r = (color >> 16) & 0xFF;
        uint8_t a = (color >> 24) & 0xFF;
        
        for (int k = 0; k < sliceWidth; k++) {
            if (x + k < SCREEN_W && y < SCREEN_H)
                mlx_put_pixel(game->img, x + k, y, (r << 24) | (g << 16) | (b << 8) | a);
        }
    }

    // Draw floor
    for (int y = endY + 1; y < SCREEN_H; y++) {
        int x = (int)(i * sliceWidth);
        for (int k = 0; k < sliceWidth; k++) {
            if (x + k < SCREEN_W && y < SCREEN_H) {
                int texX = ((x + k) * game->floor_texture.width / SCREEN_W) % game->floor_texture.width;
                int texY = ((y - endY) * game->floor_texture.height / (SCREEN_H - endY)) % game->floor_texture.height;
                uint32_t color = game->floor_texture.pixels[texY * game->floor_texture.width + texX];
                // MLX42 expects RGBA format (each component 8 bits)
                uint8_t b = (color >> 0) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t r = (color >> 16) & 0xFF;
                uint8_t a = (color >> 24) & 0xFF;
                mlx_put_pixel(game->img, x + k, y, (r << 24) | (g << 16) | (b << 8) | a);
            }
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
        
        // Calculate wall X coordinate for texture mapping
        double wallX = x - floor(x);
        if (fabs(dy) > fabs(dx))
            wallX = y - floor(y);

        draw_wall_slice(game, i, wallHeight, sliceWidth, wallX);
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

void load_textures(t_game *game) {
    // Load wall texture
    game->wall_texture.texture = mlx_load_png("textures/wall.png");
    if (!game->wall_texture.texture) {
        fprintf(stderr, "Error loading wall texture\n");
        exit(EXIT_FAILURE);
    }
    game->wall_texture.pixels = (uint32_t*)game->wall_texture.texture->pixels;
    game->wall_texture.width = game->wall_texture.texture->width;
    game->wall_texture.height = game->wall_texture.texture->height;

    // Load floor texture
    game->floor_texture.texture = mlx_load_png("textures/floor.png");
    if (!game->floor_texture.texture) {
        mlx_delete_texture(game->wall_texture.texture);
        fprintf(stderr, "Error loading floor texture\n");
        exit(EXIT_FAILURE);
    }
    game->floor_texture.pixels = (uint32_t*)game->floor_texture.texture->pixels;
    game->floor_texture.width = game->floor_texture.texture->width;
    game->floor_texture.height = game->floor_texture.texture->height;

    // Load ceiling texture
    game->ceiling_texture.texture = mlx_load_png("textures/ceiling.png");
    if (!game->ceiling_texture.texture) {
        mlx_delete_texture(game->wall_texture.texture);
        mlx_delete_texture(game->floor_texture.texture);
        fprintf(stderr, "Error loading ceiling texture\n");
        exit(EXIT_FAILURE);
    }
    game->ceiling_texture.pixels = (uint32_t*)game->ceiling_texture.texture->pixels;
    game->ceiling_texture.width = game->ceiling_texture.texture->width;
    game->ceiling_texture.height = game->ceiling_texture.texture->height;

    // Debug first pixels
    printf("First wall pixel: B:%d G:%d R:%d A:%d\n", 
        game->wall_texture.pixels[0] & 0xFF,
        (game->wall_texture.pixels[0] >> 8) & 0xFF,
        (game->wall_texture.pixels[0] >> 16) & 0xFF,
        (game->wall_texture.pixels[0] >> 24) & 0xFF);
}

void cleanup_textures(t_game *game) {
    mlx_delete_texture(game->wall_texture.texture);
    mlx_delete_texture(game->floor_texture.texture);
    mlx_delete_texture(game->ceiling_texture.texture);
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

    load_textures(&game);

    mlx_key_hook(game.mlx, key_callback, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);

    cleanup_textures(&game);
    mlx_delete_image(game.mlx, game.img);
    mlx_terminate(game.mlx);

    return EXIT_SUCCESS;
}