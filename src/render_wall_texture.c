/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:31:11 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/15 09:31:24 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void render_wall_texture(const t_game *game, int x)
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
	tex_x = (int)(wall_x * (double)WALL_W);
	if (game->data.side == 0 && game->data.ray_dir_x > 0)
		tex_x = WALL_W - tex_x - 1;
	if (game->data.side == 1 && game->data.ray_dir_y < 0)
		tex_x = WALL_W - tex_x - 1;
	wall_player_ratio = 1.0 * WALL_H / game->data.line_height;
	tex_pos = (game->data.draw_start - SCREEN_H / 2 + game->data.line_height / 2) * wall_player_ratio;
	y = game->data.draw_start;
	while (y <= game->data.draw_end)
	{
		int tex_y = (int)tex_pos & (WALL_H - 1);
		tex_pos += wall_player_ratio;
		pixel = &game->data.wall_img->pixels[(tex_y * WALL_W + tex_x) * 4];
		mlx_put_pixel(game->main_img, x, y, get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]));
		y++;
	}
}
