/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:45:41 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/22 14:05:33 by erybolov         ###   ########.fr       */
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

typedef struct s_data
{
	int			map[MAP_H][MAP_W];
	int			map_x; //current player pos
	int			map_y;
	int			step_x; //direction to step
	int			step_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			side; //wall hit side
	bool		hit;
	double		pos_x; //player pos
	double		pos_y;
	double		dir_x; //player initial direction
	double		dir_y;
	double		plane_x; //plane fov
	double		plane_y;
	double		camera_x; //normalized camera coordinate [-1 to 1]
	double		ray_dir_x; //ray direction
	double		ray_dir_y;
	double		side_dist_x; //distance to next vertical line
	double		side_dist_y; //distance to next horizontal line
	double		delta_dist_x; //distance between vertical lines
	double		delta_dist_y; //distance between horizontal lines
	double		perp_wall_dist; //util to calc ray length
	uint32_t	wall_color; //different for n s w e
}	t_data;

typedef struct s_textures
{
	mlx_texture_t	*wall_n;
	mlx_texture_t	*wall_s;
	mlx_texture_t	*wall_w;
	mlx_texture_t	*wall_e;
	mlx_image_t		*wall_n_img;
	mlx_image_t		*wall_s_img;
	mlx_image_t		*wall_w_img;
	mlx_image_t		*wall_e_img;
} t_textures;

typedef struct    s_game
{
	mlx_t			*mlx;
	mlx_image_t		*main_img;
	t_data			data;
	t_textures		textures;
}	t_game;

#endif