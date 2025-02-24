/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:18:19 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/22 10:34:54 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	raycast_01(t_game *game)
{
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
		game->data.side_dist_x = \
		(game->data.pos_x - game->data.map_x) * game->data.delta_dist_x;
	}
	else
	{
		game->data.step_x = 1;
		game->data.side_dist_x = \
		(game->data.map_x + 1.0 - game->data.pos_x) * game->data.delta_dist_x;
	}
}

static void	raycast_02(t_game *game)
{
	if (game->data.ray_dir_y < 0)
	{
		game->data.step_y = -1;
		game->data.side_dist_y = \
		(game->data.pos_y - game->data.map_y) * game->data.delta_dist_y;
	}
	else
	{
		game->data.step_y = 1;
		game->data.side_dist_y = \
		(game->data.map_y + 1.0 - game->data.pos_y) * game->data.delta_dist_y;
	}
}

static void	raycast_03(t_game *game)
{
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
		if (game->map->cell_value[game->data.map_y][game->data.map_x] != '0')
			game->data.hit = true;
	}
	if (game->data.side == 0)
		game->data.perp_wall_dist = \
	game->data.side_dist_x - game->data.delta_dist_x;
	else
		game->data.perp_wall_dist = \
	game->data.side_dist_y - game->data.delta_dist_y;
}

static void	raycast_04(t_game *game)
{
	game->data.line_height = (int)(SCREEN_H / game->data.perp_wall_dist);
	game->data.draw_start = -game->data.line_height / 2 + SCREEN_H / 2;
	if (game->data.draw_start < 0)
		game->data.draw_start = 0;
	game->data.draw_end = game->data.line_height / 2 + SCREEN_H / 2;
	if (game->data.draw_end >= SCREEN_H)
		game->data.draw_end = SCREEN_H - 1;
	if (game->data.side == 1)
	{
		if (game->data.ray_dir_y > 0)
			game->data.wall_img = game->textures.wall_s_img;
		else
			game->data.wall_img = game->textures.wall_n_img;
	}
	else
	{
		if (game->data.ray_dir_x > 0)
			game->data.wall_img = game->textures.wall_e_img;
		else
			game->data.wall_img = game->textures.wall_w_img;
	}
}

void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_W)
	{
		game->data.hit = false;
		game->data.camera_x = 2 * x / (double)SCREEN_W - 1;
		game->data.ray_dir_x = game->data.dir_x + \
		game->data.plane_x * game->data.camera_x;
		game->data.ray_dir_y = game->data.dir_y + \
		game->data.plane_y * game->data.camera_x;
		game->data.map_x = (int)game->data.pos_x;
		game->data.map_y = (int)game->data.pos_y;
		raycast_01(game);
		raycast_02(game);
		raycast_03(game);
		raycast_04(game);
		render_wall_texture(game, x);
		x++;
	}
}
