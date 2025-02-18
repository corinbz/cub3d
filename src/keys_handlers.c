/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:10:28 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/18 12:13:40 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

void	mouse_handler(double xpos, double ypos, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->data.mouse_x = xpos;
	game->data.mouse_y = ypos;
}

void check_keys_w_s(t_game* g)
{
    double  move_speed;

    move_speed = g->mlx->delta_time * 5.0;
    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
    {
        if (g->map->cell_value[(int)g->data.pos_y][(int)(g->data.pos_x + g->data.dir_x * move_speed)] == '0')
            g->data.pos_x += g->data.dir_x * move_speed;
        if (g->map->cell_value[(int)(g->data.pos_y + g->data.dir_y * move_speed)][(int)g->data.pos_x] == '0')
            g->data.pos_y += g->data.dir_y * move_speed;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
    {
        if (g->map->cell_value[(int)g->data.pos_y][(int)(g->data.pos_x - g->data.dir_x * move_speed)] == '0')
            g->data.pos_x -= g->data.dir_x * move_speed;
        if (g->map->cell_value[(int)(g->data.pos_y - g->data.dir_y * move_speed)][(int)g->data.pos_x] == '0')
            g->data.pos_y -= g->data.dir_y * move_speed;
    }
}

void check_keys_a_d(t_game* g)
{
    double  rot_speed;
    double old_dir_x;
    double old_plane_x;

    rot_speed = g->mlx->delta_time * 2.0;
    if (mlx_is_key_down(g->mlx, MLX_KEY_D) || g->data.mouse_x > (3 * SCREEN_W / 4))
    {
        old_dir_x = g->data.dir_x;
        g->data.dir_x = g->data.dir_x * cos(-rot_speed) - g->data.dir_y * sin(-rot_speed);
        g->data.dir_y = old_dir_x * sin(-rot_speed) + g->data.dir_y * cos(-rot_speed);
        old_plane_x = g->data.plane_x;
        g->data.plane_x = g->data.plane_x * cos(-rot_speed) - g->data.plane_y * sin(-rot_speed);
        g->data.plane_y = old_plane_x * sin(-rot_speed) + g->data.plane_y * cos(-rot_speed);
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_A) || g->data.mouse_x < (SCREEN_W / 4))
    {
        old_dir_x = g->data.dir_x;
        g->data.dir_x = g->data.dir_x * cos(rot_speed) - g->data.dir_y * sin(rot_speed);
        g->data.dir_y = old_dir_x * sin(rot_speed) + g->data.dir_y * cos(rot_speed);
        old_plane_x = g->data.plane_x;
        g->data.plane_x = g->data.plane_x * cos(rot_speed) - g->data.plane_y * sin(rot_speed);
        g->data.plane_y = old_plane_x * sin(rot_speed) + g->data.plane_y * cos(rot_speed);
    }
}
