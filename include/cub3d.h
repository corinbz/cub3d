/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:45:41 by ccraciun          #+#    #+#             */
/*   Updated: 2024/11/28 23:05:41 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include "../MLX42/include/MLX42/MLX42.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define MAP_W 9
#define MAP_H 10

typedef struct    s_player
{
	double x;
	double y;
	double angle;
	double fov;
}	t_player;

typedef struct    s_cub3d
{
	int				map[MAP_H][MAP_W];
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*mlx_image;
	bool			keyState[512];
}	t_cub3d;

#endif