/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:45:41 by ccraciun          #+#    #+#             */
/*   Updated: 2025/02/16 15:08:38 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include "../MLX42/include/MLX42/MLX42.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define MAP_W 10
#define MAP_H 10
#define WALL_W 64
#define WALL_H 64

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#define FILE_NO_ACCES "File could not be opened"

//STRUCTS

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
	char	player_dir;
	double	player_x;
	double	player_y;
	int		total_ln;
}	t_map;

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
	double		mouse_x;
	double		mouse_y;
	mlx_image_t	*wall_img; //different for n s w e
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

typedef struct s_game
{
	mlx_t					*mlx;
	t_map					*map;
	mlx_image_t				*main_img;
	t_data					data; //TODO use ptr?
	t_textures				textures; //TODO use ptr?
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
void	count_file_lines(int fd, t_map *map);
bool	check_map_complete(t_map *map);

//parse_colors.c
bool parse_colors(char *line, t_map *map);

//parse_img_paths
bool parse_paths(char *line, t_map *map);



//helpers
uint32_t	get_rgba(int r, int g, int b, int a);
void		print_mlx_error_and_exit(void);
void		cleanup_and_terminate_mlx(t_game *game);

//callbacks
void		key_callback(mlx_key_data_t keydata, void* param);
void mouse_handler(double xpos, double ypos, void* param);

//game loop and render
void		game_loop(void *param);
void		draw_floor(const t_game *game);
void		draw_ceiling(const t_game *game);
void		render_wall_texture(const t_game *game, int x);

#endif