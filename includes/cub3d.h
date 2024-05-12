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

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libmms/libmms.h"
# include "../libs/libftms/inc/libft.h"
# include "../libs/memory_manager/mm_features/mm_utils.h"
# include "../libs/memory_manager/memory_manager.h"



typedef s_map
{
	char	**map;
	size_t	width;
	size_t	height;
}			t_map;

typedef s_game
{
	unsigned int	floor_color;
	unsigned int	sky_color;
} t_game;

#endif
