/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/22 14:23:53 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


//helpers; move later
void put_vertical_line(mlx_image_t* img, uint32_t x, uint32_t y1, uint32_t y2, uint32_t color)
{
    uint32_t temp;
    uint32_t y;

    if (y2 < y1)
    {
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    if (x >= img->width || y1 >= img->height)
        return;
    if (y2 >= img->height)
        y2 = img->height - 1;
    y = y1;
    while (y <= y2)
    {
        mlx_put_pixel(img, x, y, color);
        y++;
    }
}

void print_mlx_error_and_exit(void)
{
    printf("MLX error: %s\n", mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}

void game_loop(void *param)
{
    t_game *game;
    int x;

    game = (t_game *)param;
    x = 0;
    memset(game->main_img->pixels, 0, game->main_img->width * game->main_img->height * sizeof(int32_t));

    while (x < SCREEN_W)
    {
        game->data.hit = false;
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
        if (game->data.side == 0)
            game->data.perp_wall_dist = game->data.side_dist_x - game->data.delta_dist_x;
        else
            game->data.perp_wall_dist = game->data.side_dist_y - game->data.delta_dist_y;
        game->data.line_height = (int)(SCREEN_H / game->data.perp_wall_dist);
        game->data.draw_start = -game->data.line_height / 2 + SCREEN_H / 2;
        if (game->data.draw_start < 0)
            game->data.draw_start = 0;
        game->data.draw_end = game->data.line_height / 2 + SCREEN_H / 2;
        if (game->data.draw_end >= SCREEN_H)
            game->data.draw_end = SCREEN_H - 1;
        if (game->data.side == 1)
            if (game->data.ray_dir_y > 0)
                game->data.wall_color = 0xFF0000FF;
            else
                game->data.wall_color = 0x00FF00FF;
        else
            if (game->data.ray_dir_x > 0)
                game->data.wall_color = 0x0000FFFF;
            else
                game->data.wall_color = 0xFFFF00FF;
        put_vertical_line(game->main_img, x, game->data.draw_start, game->data.draw_end, game->data.wall_color);
        x++;
    }
}

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
        {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    memcpy(game->data.map, map, sizeof(map));


    game->data.pos_x = 1;
    game->data.pos_y = 1;
    game->data.dir_x = -1;
    game->data.dir_y = 0;
    game->data.plane_x = 0;
    game->data.plane_y = 0.66;
}

void key_callback(mlx_key_data_t keydata, void* param)
{
    t_game  *game;
    double  move_speed;
    double  rot_speed;
    double  old_dir_x;
    double  old_plane_x;

    game = (t_game *)param;
    move_speed = game->mlx->delta_time * 5.0;
    rot_speed = game->mlx->delta_time * 3.0;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
    {
        if (game->data.map[(int)(game->data.pos_x + game->data.dir_x * move_speed)][(int)game->data.pos_y] == 0)
            game->data.pos_x += game->data.dir_x * move_speed;
        if (game->data.map[(int)game->data.pos_x][(int)(game->data.pos_y + game->data.dir_y * move_speed)] == 0)
            game->data.pos_y += game->data.dir_y * move_speed;
    }
    if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
    {
        if (game->data.map[(int)(game->data.pos_x - game->data.dir_x * move_speed)][(int)game->data.pos_y] == 0)
            game->data.pos_x -= game->data.dir_x * move_speed;
        if (game->data.map[(int)game->data.pos_x][(int)(game->data.pos_y - game->data.dir_y * move_speed)] == 0)
            game->data.pos_y -= game->data.dir_y * move_speed;
    }
    if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
    {
        old_dir_x = game->data.dir_x;
        game->data.dir_x = game->data.dir_x * cos(-rot_speed) - game->data.dir_y * sin(-rot_speed);
        game->data.dir_y = old_dir_x * sin(-rot_speed) + game->data.dir_y * cos(-rot_speed);
        old_plane_x = game->data.plane_x;
        game->data.plane_x = game->data.plane_x * cos(-rot_speed) - game->data.plane_y * sin(-rot_speed);
        game->data.plane_y = old_plane_x * sin(-rot_speed) + game->data.plane_y * cos(-rot_speed);
    }
    if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
    {
        old_dir_x = game->data.dir_x;
        game->data.dir_x = game->data.dir_x * cos(rot_speed) - game->data.dir_y * sin(rot_speed);
        game->data.dir_y = old_dir_x * sin(rot_speed) + game->data.dir_y * cos(rot_speed);
        old_plane_x = game->data.plane_x;
        game->data.plane_x = game->data.plane_x * cos(rot_speed) - game->data.plane_y * sin(rot_speed);
        game->data.plane_y = old_plane_x * sin(rot_speed) + game->data.plane_y * cos(rot_speed);
    }
}

int main() {
    t_game game = {0};

    prepare_and_load_textures(&game);

    mlx_key_hook(game.mlx, &key_callback, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);

    mlx_delete_image(game.mlx, game.main_img); //make clean up func to delete textures as well
    mlx_terminate(game.mlx);

    return EXIT_SUCCESS;
}