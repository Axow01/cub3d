/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:07:19 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/12 18:10:16 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_CUB3D
# define H_CUB3D

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libmms/libmms.h"
# include "../libs/libftms/inc/libft.h"

# define ALLOWED_CHARS " 01NSEW"

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

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	double	angle;
}	t_player;

typedef struct s_game
{
	t_map			map;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;

} t_game;


char    at_pos(t_map *map, size_t x, size_t y);
void    set_pos(t_map *map, size_t x, size_t y, char val);

// PARSING
bool    parse_file(t_game *game, char *filename);
bool	parse_headers(t_game *instance, int fd);
bool    validate_map(t_game *game, int fd);

#endif
