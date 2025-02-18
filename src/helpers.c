/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 06:50:42 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/18 12:57:14 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	print_mlx_error_clean_exit(t_game *game)
{
	printf("MLX error: %s\n", mlx_strerror(mlx_errno));
	cleanup_and_terminate_mlx(game);
	exit(EXIT_FAILURE);
}

void	cleanup_and_terminate_mlx(t_game *game)
{
	if (game && game->map)
		free_map(game->map);
	if (game && game->textures.wall_n)
		mlx_delete_texture(game->textures.wall_n);
	if (game && game->textures.wall_s)
		mlx_delete_texture(game->textures.wall_s);
	if (game && game->textures.wall_w)
		mlx_delete_texture(game->textures.wall_w);
	if (game && game->textures.wall_e)
		mlx_delete_texture(game->textures.wall_e);
	if (game && game->mlx && game->textures.wall_n_img)
		mlx_delete_image(game->mlx, game->textures.wall_n_img);
	if (game && game->mlx && game->textures.wall_s_img)
		mlx_delete_image(game->mlx, game->textures.wall_s_img);
	if (game && game->mlx && game->textures.wall_w_img)
		mlx_delete_image(game->mlx, game->textures.wall_w_img);
	if (game && game->mlx && game->textures.wall_e_img)
		mlx_delete_image(game->mlx, game->textures.wall_e_img);
	if (game && game->mlx && game->main_img)
		mlx_delete_image(game->mlx, game->main_img);
	if (game && game->mlx)
		mlx_terminate(game->mlx);
	if (game)
		free(game);
}
