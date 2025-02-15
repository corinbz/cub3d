/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:24:17 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/15 09:31:26 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_ceiling(const t_game *game)
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

void draw_floor(const t_game *game)
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
    t_game  *game;
    int     x;
    double  move_speed;
    double  rot_speed;
    double  old_dir_x;
    double  old_plane_x;

    game = (t_game *)param;
    x = 0;
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
