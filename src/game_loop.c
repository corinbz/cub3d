/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:24:17 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/21 22:09:40 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_ceiling(const t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H / 2)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			mlx_put_pixel(game->main_img, x, y,
				get_rgba(game->map->ceiling_color[0], \
				game->map->ceiling_color[1], game->map->ceiling_color[2], 255));
			x++;
		}
		y++;
	}
}

void	draw_floor(const t_game *game)
{
	int	x;
	int	y;

	y = SCREEN_H / 2;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			mlx_put_pixel(game->main_img, x, y, \
			get_rgba(game->map->floor_color[0], game->map->floor_color[1], \
			game->map->floor_color[2], 255));
			x++;
		}
		y++;
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	check_keys_w_s(game);
	check_keys_a_d(game);
	check_keys_l_r(game);
	draw_ceiling(game);
	draw_floor(game);
	raycast(game);
}
