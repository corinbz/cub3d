/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/11/28 21:46:32 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(void)
{
	t_cub3d	cub3d;

	cub3d.mlx = mlx_init(SCREEN_W, SCREEN_H, "nov 28 raycasting example", true);
	if (!cub3d.mlx) {
		fprintf(stderr, "MLX42 initialisation failed!\n");
		return 1;
	}

	cub3d.mlx_image = mlx_new_image(cub3d.mlx, SCREEN_W, SCREEN_H);
	if (!cub3d.mlx_image)
	{
		fprintf(stderr, "MLX42 image creation failed!\n");
		mlx_terminate(cub3d.mlx);
		return 1;
	}

	mlx_image_to_window(cub3d.mlx, cub3d.mlx_image, 0, 0);

	cub3d.player.x = 1;
	cub3d.player.y = 1;
	cub3d.player.angle = 1;
	cub3d.player.fov = M_PI_4;

	const int map_example[10][9] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	for (int i = 0; i < MAP_H; i++)
		for (int j = 0; j < MAP_W; j++)
			cub3d.map[i][j] = map_example[i][j];

	//mlx loop hook
	//mlx key hook

	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);

	return (0);
}
