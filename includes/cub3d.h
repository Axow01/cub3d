/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:07:19 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/17 20:00:05 by tparadis         ###   ########.fr       */
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
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pAngle;
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

} t_game;

// MAP UTILS
char    at_pos(t_map *map, size_t x, size_t y);
void    set_pos(t_map *map, size_t x, size_t y, char val);

// PARSING
bool    parse_file(t_game *game, char *filename);
bool	parse_headers(t_game *instance, int fd);
bool    parse_map(t_game *game, int fd);

// RAYCAST
void		key_hook(mlx_key_data_t keydata, void *param);
t_player	*init_player(t_game *game, float x, float y, char angle);

// RENDERING
void	update_minimap(t_game *game);

// MINIMAP
bool	initialize_minimap(t_game *game);

#endif