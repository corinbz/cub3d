/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:45:41 by ccraciun          #+#    #+#             */
/*   Updated: 2024/12/08 22:53:22 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define MAP_W 10
#define MAP_H 10
#define RAYS 200

typedef struct s_texture {
    mlx_texture_t *texture;
    uint32_t *pixels;
    uint32_t width;
    uint32_t height;
} t_texture;

typedef struct    s_player
{
	double x;
	double y;
	double angle;
	double fov;
}	t_player;

typedef struct    s_game
{
	int				map[MAP_H][MAP_W];
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	bool			keyState[512];
	t_texture		wall_texture;
	t_texture		floor_texture;
	t_texture		ceiling_texture;
}	t_game;

void load_textures(t_game *game);
void cleanup_textures(t_game *game);

#endif