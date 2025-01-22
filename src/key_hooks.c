/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:45:54 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/22 13:58:45 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_close_window(game->mlx);
	}
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		printf("pressed W\n");
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		printf("pressed S\n");
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		printf("pressed D\n");
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		printf("pressed D\n");
}
