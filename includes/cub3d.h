/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:07:19 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/23 00:29:42 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libmms/libmms.h"
# include "../libs/libftms/inc/libft.h"

# define ALLOWED_CHARS " 01NSEW"
# define PI 3.14159

# define WINDOW_HEIGHT 800
# define WINDOW_WIDTH 1024

# define MINIMAP_SIZE 100
# define ROT_SPEED 0.05

typedef struct s_line
{
	size_t	size;
	char	*line;
}			t_line;

typedef struct s_map
{
	t_line	*grid;
	size_t	size;
}			t_map;

typedef struct s_minimap
{
	mlx_image_t	*minimap_img;
}				t_minimap;

typedef struct	s_player {
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	planex;
	double	planey;
}			t_player;

typedef struct s_game
{
	t_map			map;
	t_minimap		minimap;
	t_player		player;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	mlx_t			*mlx;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	mlx_image_t		*wall;
	mlx_image_t		*floor_ceiling;
} t_game;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		side;
}			t_ray;

typedef struct	s_wall
{
	int		height;
	int		start;
	int		end;
	int		x;
	double	distance;
	double	camera;
}		t_wall;

// MAP UTILS
char    at_pos(t_map *map, size_t x, size_t y);
void    set_pos(t_map *map, size_t x, size_t y, char val);

// PARSING
bool    parse_file(t_game *game, char *filename);
bool	parse_headers(t_game *instance, int fd);
bool    parse_map(t_game *game, int fd);

// RAYCAST
void		key_hook(mlx_key_data_t keydata, void *param);
void		raycast(t_game *game);

// RENDERING
void	update_minimap(t_game *game);
void	draw_floor_ceiling(t_game *game);

// MINIMAP
bool	initialize_minimap(t_game *game);

// INIT
void	init_player(t_player *player, float x, float y, char angle); 

#endif
