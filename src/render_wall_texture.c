/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:31:11 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/18 10:47:43 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calculate_texture_coordinates(const t_game *game,
			double *wall_x, int *tex_x, double *wall_player_ratio)
{
	if (game->data.side == 0)
		*wall_x = game->data.pos_y + game->data.perp_wall_dist
			* game->data.ray_dir_y;
	else
		*wall_x = game->data.pos_x + game->data.perp_wall_dist
			* game->data.ray_dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * (double)WALL_W);
	if (game->data.side == 0 && game->data.ray_dir_x > 0)
		*tex_x = WALL_W - *tex_x - 1;
	if (game->data.side == 1 && game->data.ray_dir_y < 0)
		*tex_x = WALL_W - *tex_x - 1;
	*wall_player_ratio = 1.0 * WALL_H / game->data.line_height;
}

static void	draw_vertical_line(const t_game *game, int x, int tex_x,
			double wall_player_ratio)
{
	double	tex_pos;
	int		y;
	uint8_t	*pixel;
	int		tex_y;

	tex_pos = (game->data.draw_start - SCREEN_H / 2
			+ game->data.line_height / 2) * wall_player_ratio;
	y = game->data.draw_start;
	while (y <= game->data.draw_end)
	{
		tex_y = (int)tex_pos & (WALL_H - 1);
		pixel = &game->data.wall_img->pixels[(tex_y * WALL_W + tex_x) * 4];
		mlx_put_pixel(game->main_img, x, y,
			get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]));
		tex_pos += wall_player_ratio;
		y++;
	}
}

void	render_wall_texture(const t_game *game, int x)
{
	double	wall_x;
	double	wall_player_ratio;
	int		tex_x;

	calculate_texture_coordinates(game, &wall_x, &tex_x, &wall_player_ratio);
	draw_vertical_line(game, x, tex_x, wall_player_ratio);
}
