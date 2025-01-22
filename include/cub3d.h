/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:45:41 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/22 13:51:27 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>

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
	bool	valid;
	int		floor_color[3];
	bool	floor_color_filled;
	int		ceiling_color[3];
	bool	ceiling_color_filled;
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
void	mlx_error(void);
bool	dsp_err(char *err);

//utils
char	*get_next_line(int fd, bool clean);
void	ft_free_all(char **str1, char **str2, char **str3);
int		contains_newline(const char *s);
char	*join_strs(const char *s1, const char *s2);
char	*ft_strdup(const char *str);

//utils_memory.c
void	*ft_calloc(size_t num_elements, size_t element_size);
void	ft_free_2d(char **arr);

//utils_strings.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	strip_whitespace(char *str);
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_isspace(char c);

//split.c
char	**ft_split(char const *s, char c);

//free_structs.c
void	free_map(t_map *map);

//map_parsing.c
bool	parse_map_file(char *path, t_map *map);

//check_map_basic.c
int		count_rows(char **cells);
bool	check_f_or_l(char *row);
bool	check_sides(char *row);
bool	valid_map(t_map *map);

//check_map_space.c
bool	check_space_neighbours(char **map);

//check_map_lines.c
bool	validate_rows(char **map_array, int max_rows);

//utils_files.c
bool	file_exists_open(const char *filename);

//parse_colors.c
bool parse_colors(char *line, t_map *map);

//parse_img_paths
bool parse_paths(char *line, t_map *map);

//key_hooks.c
void	ft_keyhooks(mlx_key_data_t keydata, void *param);