/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/11/28 23:06:12 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d = param;
	if (keydata.action == MLX_PRESS)
		cub3d->keyState[keydata.key] = true;
	else if (keydata.action == MLX_RELEASE)
		cub3d->keyState[keydata.key] = false;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cub3d->mlx);
}

bool	is_player_touching_wall(t_cub3d *cub3d)
{
	int	floor_x = floor(cub3d->player.x);
	int	floor_y = floor(cub3d->player.y);

	if (floor_x < 0 || floor_x >= MAP_W || floor_y < 0 || floor_y >= MAP_H)
		return (true);

	return (cub3d->map[floor_y][floor_x] != 0);
}

void	update_player(t_cub3d *cub3d)
{
	double	speed = 0.025;
	double	angular_speed = 0.025;

	double old_x = cub3d->player.x;
	double old_y = cub3d->player.y;

	if (cub3d->keyState[MLX_KEY_W])
	{
		cub3d->player.x += cos(cub3d->player.angle) * speed;
		cub3d->player.y += sin(cub3d->player.angle) * speed;
	}
	if (cub3d->keyState[MLX_KEY_S])
	{
		cub3d->player.x -= cos(cub3d->player.angle) * speed;
		cub3d->player.y -= sin(cub3d->player.angle) * speed;
	}
	if (cub3d->keyState[MLX_KEY_A])
	{
		cub3d->player.angle -= angular_speed;
	}
	if (cub3d->keyState[MLX_KEY_D])
	{
		cub3d->player.angle += angular_speed;
	}

	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * M_PI;
	if (cub3d->player.angle >= 2 * M_PI)
		cub3d->player.angle -= 2 * M_PI;

	if (is_player_touching_wall(cub3d))
	{
		cub3d->player.x = old_x;
		cub3d->player.y = old_y;
	}
}

void	game_loop(void *param)
{
	t_cub3d	*cub3d = param;
	mlx_delete_image(cub3d->mlx, cub3d->mlx_image);
	cub3d->mlx_image = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);

}

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

	mlx_key_hook(cub3d.mlx, key_hook, &cub3d);
	//mlx loop hook

	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);

	return (0);
}
