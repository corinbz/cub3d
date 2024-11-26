/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:45:41 by ccraciun          #+#    #+#             */
/*   Updated: 2024/11/26 10:49:48 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#define WIDTH 512
#define HEIGHT 512

//STRUCTS
typedef struct s_textures
{
	mlx_texture_t	*blue_brk;
	mlx_texture_t	*grey_brk;
	mlx_texture_t	*purple_brk;
	mlx_texture_t	*yellow_brk;
}	t_textures;

typedef struct s_imgs
{
	mlx_image_t	*blue_brk;
	mlx_image_t	*grey_brk;
	mlx_image_t	*purple_brk;
	mlx_image_t	*yellow_brk;
}	t_imgs;

typedef struct s_map
{
	char	**cell_value;
	size_t	width;
	size_t	height;
	bool	valid;
}	t_map;

typedef struct s_player_pos
{
	size_t	x;
	size_t	y;
}	t_player_pos;

typedef struct s_game
{
	mlx_t					*mlx;
	t_player_pos			*player_pos;
	t_map					*map;
	t_imgs					*imgs;
}	t_game;

//FUNCTIONS