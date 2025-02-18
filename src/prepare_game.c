/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:01:50 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/18 12:23:13 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_player_direction(t_game *game)
{
	char	direction;

	direction = game->map->cell_value
	[(int)game->data.pos_y]
	[(int)game->data.pos_x];
	if (direction == 'W')
	{
		game->data.dir_x = 1;
		game->data.plane_y = -0.66;
	}
	else if (direction == 'E')
	{
		game->data.dir_x = -1;
		game->data.plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		game->data.dir_y = -1;
		game->data.plane_x = -0.66;
	}
	else if (direction == 'N')
	{
		game->data.dir_y = 1;
		game->data.plane_x = 0.66;
	}
}

static void	load_textures(t_game *game)
{
	game->textures.wall_n = mlx_load_png(game->map->north_png_path);
	if (!game->textures.wall_n)
		print_mlx_error_clean_exit(game);
	game->textures.wall_s = mlx_load_png(game->map->south_png_path);
	if (!game->textures.wall_s)
		print_mlx_error_clean_exit(game);
	game->textures.wall_w = mlx_load_png(game->map->west_png_path);
	if (!game->textures.wall_w)
		print_mlx_error_clean_exit(game);
	game->textures.wall_e = mlx_load_png(game->map->east_png_path);
	if (!game->textures.wall_e)
		print_mlx_error_clean_exit(game);
}

static void	create_texture_images(t_game *game)
{
	game->textures.wall_n_img = mlx_texture_to_image(game->mlx,
			game->textures.wall_n);
	if (!game->textures.wall_n_img
		|| !mlx_resize_image(game->textures.wall_n_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);
	game->textures.wall_s_img = mlx_texture_to_image(game->mlx,
			game->textures.wall_s);
	if (!game->textures.wall_s_img
		|| !mlx_resize_image(game->textures.wall_s_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);
	game->textures.wall_w_img = mlx_texture_to_image(game->mlx,
			game->textures.wall_w);
	if (!game->textures.wall_w_img
		|| !mlx_resize_image(game->textures.wall_w_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);
	game->textures.wall_e_img = mlx_texture_to_image(game->mlx,
			game->textures.wall_e);
	if (!game->textures.wall_e_img
		|| !mlx_resize_image(game->textures.wall_e_img, WALL_W, WALL_H))
		print_mlx_error_clean_exit(game);
}

static void	init_window_and_image(t_game *game)
{
	game->mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3d", false);
	if (!game->mlx)
		print_mlx_error_clean_exit(game);
	game->main_img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (!game->main_img
		|| (mlx_image_to_window(game->mlx, game->main_img, 0, 0) < 0))
		print_mlx_error_clean_exit(game);
}

void	prepare_game(t_game *game)
{
	init_window_and_image(game);
	load_textures(game);
	create_texture_images(game);
	game->data.pos_x = game->map->player_x;
	game->data.pos_y = game->map->player_y;
	set_player_direction(game);
	game->map->cell_value[(int)game->data.pos_y][(int)game->data.pos_x] = '0';
	game->data.pos_y += 0.5;
	game->data.pos_x += 0.5;
}
