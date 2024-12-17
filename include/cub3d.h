/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:45:41 by ccraciun          #+#    #+#             */
/*   Updated: 2024/12/17 12:58:11 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
# include <fcntl.h>
# include <stddef.h>

#define WIN_WIDTH 1080
#define WIN_HEIGHT 1080

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#define FILE_NO_ACCES "File could not be opened"

//STRUCTS
typedef struct s_textures
{
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
}	t_textures;

typedef struct s_imgs
{
	mlx_image_t	*NO;
	mlx_image_t	*SO;
	mlx_image_t	*WE;
	mlx_image_t	*EA;
}	t_imgs;

typedef struct s_map
{
	char	*north_png_path;
	char	*south_png_path;
	char	*west_png_path;
	char	*east_png_path;
	char	**cell_value;
	size_t	width;
	size_t	height;
	bool	valid;
	int		floor_color[3];
	int		ceiling_color[3];
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

//errors.c
void mlx_error(void);

//utils
char	*get_next_line(int fd);
void	ft_free_all(char **str1, char **str2, char **str3);
int		contains_newline(const char *s);
char	*join_strs(const char *s1, const char *s2);
char	*ft_strdup(const char *str);

//utils_memory.c
void	*ft_calloc(size_t num_elements, size_t element_size);
void	ft_free_2d(char **arr);

//utils_strings.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void 	strip_whitespace(char *str);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_isspace(char c);

//split.c
char	**ft_split(char const *s, char c);

//free_structs.c
void	free_map(t_map *map);

//map_parsing.c
int parse_map_file(char *path, t_map *map);

//check_map.c
bool	valid_walls(t_map *map);