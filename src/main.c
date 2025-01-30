/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/30 23:01:36 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


//helpers; move later
uint32_t    get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void print_mlx_error_and_exit(void)
{
    printf("MLX error: %s\n", mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}

void render_wall_texture(t_game *game, int x)
{
    double  wall_x;
    double  wall_player_ratio;
    double  tex_pos;
    int     tex_x;
    int     y;
    uint8_t *pixel;
    
    if (game->data.side == 0)
        wall_x = game->data.pos_y + game->data.perp_wall_dist * game->data.ray_dir_y;
    else
        wall_x = game->data.pos_x + game->data.perp_wall_dist * game->data.ray_dir_x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)WALL_IMG_W);
    if (game->data.side == 0 && game->data.ray_dir_x > 0)
        tex_x = WALL_IMG_W - tex_x - 1;
    if (game->data.side == 1 && game->data.ray_dir_y < 0)
        tex_x = WALL_IMG_W - tex_x - 1;
    wall_player_ratio = 1.0 * WALL_IMG_H / game->data.line_height;
    tex_pos = (game->data.draw_start - SCREEN_H / 2 + game->data.line_height / 2) * wall_player_ratio;
    y = game->data.draw_start;
    while (y <= game->data.draw_end)
    {
        int tex_y = (int)tex_pos & (WALL_IMG_H - 1);
        tex_pos += wall_player_ratio;
        pixel = (uint8_t *)&game->data.wall_img->pixels[(tex_y * WALL_IMG_W + tex_x) * 4];
        mlx_put_pixel(game->main_img, x, y, get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]));
        y++;
    }
}

void draw_ceiling(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < SCREEN_H / 2)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            mlx_put_pixel(game->main_img, x, y, get_rgba(100, 100, 255, 255));
            x++;
        }
        y++;
    }
}

void draw_floor(t_game *game)
{
    int x;
    int y;
    
    y = SCREEN_H / 2;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            mlx_put_pixel(game->main_img, x, y, get_rgba(100, 255, 100, 255));
            x++;
        }
        y++;
    }
}

void game_loop(void *param)
{
    t_game *game;
    int x;
    double  move_speed;
    double  rot_speed;
    double  old_dir_x;
    double  old_plane_x;

    game = (t_game *)param;
    x = 0;
    // printf("frame time: %f\n", 1.0/ game->mlx->delta_time);
    move_speed = game->mlx->delta_time * 5.0;
    rot_speed = game->mlx->delta_time * 3.0;
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        if (game->data.map[(int)(game->data.pos_x + game->data.dir_x * move_speed)][(int)game->data.pos_y] == 0)
            game->data.pos_x += game->data.dir_x * move_speed;
        if (game->data.map[(int)game->data.pos_x][(int)(game->data.pos_y + game->data.dir_y * move_speed)] == 0)
            game->data.pos_y += game->data.dir_y * move_speed;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        if (game->data.map[(int)(game->data.pos_x - game->data.dir_x * move_speed)][(int)game->data.pos_y] == 0)
            game->data.pos_x -= game->data.dir_x * move_speed;
        if (game->data.map[(int)game->data.pos_x][(int)(game->data.pos_y - game->data.dir_y * move_speed)] == 0)
            game->data.pos_y -= game->data.dir_y * move_speed;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        old_dir_x = game->data.dir_x;
        game->data.dir_x = game->data.dir_x * cos(-rot_speed) - game->data.dir_y * sin(-rot_speed);
        game->data.dir_y = old_dir_x * sin(-rot_speed) + game->data.dir_y * cos(-rot_speed);
        old_plane_x = game->data.plane_x;
        game->data.plane_x = game->data.plane_x * cos(-rot_speed) - game->data.plane_y * sin(-rot_speed);
        game->data.plane_y = old_plane_x * sin(-rot_speed) + game->data.plane_y * cos(-rot_speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        old_dir_x = game->data.dir_x;
        game->data.dir_x = game->data.dir_x * cos(rot_speed) - game->data.dir_y * sin(rot_speed);
        game->data.dir_y = old_dir_x * sin(rot_speed) + game->data.dir_y * cos(rot_speed);
        old_plane_x = game->data.plane_x;
        game->data.plane_x = game->data.plane_x * cos(rot_speed) - game->data.plane_y * sin(rot_speed);
        game->data.plane_y = old_plane_x * sin(rot_speed) + game->data.plane_y * cos(rot_speed);
    }

    draw_ceiling(game);
    draw_floor(game);

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
                game->data.wall_img = game->textures.wall_n_img;
            else
                game->data.wall_img = game->textures.wall_s_img;
        else
            if (game->data.ray_dir_x > 0)
                game->data.wall_img = game->textures.wall_w_img;
            else
                game->data.wall_img = game->textures.wall_e_img;
        render_wall_texture(game, x);
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

    game = (t_game *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);
}

void cleanup_and_terminate_mlx(t_game *game)
{
    mlx_delete_texture(game->textures.wall_n);
    mlx_delete_texture(game->textures.wall_s);
    mlx_delete_texture(game->textures.wall_w);
    mlx_delete_texture(game->textures.wall_e);
    mlx_delete_image(game->mlx, game->textures.wall_n_img);
    mlx_delete_image(game->mlx, game->textures.wall_s_img);
    mlx_delete_image(game->mlx, game->textures.wall_w_img);
    mlx_delete_image(game->mlx, game->textures.wall_e_img);
    mlx_delete_image(game->mlx, game->main_img);
    mlx_terminate(game->mlx);
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