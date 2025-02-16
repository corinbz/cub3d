/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_callback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:10:28 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/16 14:55:02 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void key_callback(mlx_key_data_t keydata, void* param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}
void mouse_handler(double xpos, double ypos, void* param)
{
	t_game *game;
	int     x;
    double  move_speed;
    double  rot_speed;
    double  old_dir_x;
    double  old_plane_x;
	
	game = (t_game*)param;
	x = 0;
    move_speed = game->mlx->delta_time * 5.0;
    rot_speed = game->mlx->delta_time * 3.0;
	if (xpos < 400)
    {
        old_dir_x = game->data.dir_x;
        game->data.dir_x = game->data.dir_x * cos(rot_speed) - game->data.dir_y * sin(rot_speed);
        game->data.dir_y = old_dir_x * sin(rot_speed) + game->data.dir_y * cos(rot_speed);
        old_plane_x = game->data.plane_x;
        game->data.plane_x = game->data.plane_x * cos(rot_speed) - game->data.plane_y * sin(rot_speed);
        game->data.plane_y = old_plane_x * sin(rot_speed) + game->data.plane_y * cos(rot_speed);
    }
    // param is your data structure passed from main
    // xpos and ypos are the current mouse coordinates
    printf("Mouse position: x: %f, y: %f\n", xpos, ypos);
}