/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:36:42 by mmarcott          #+#    #+#             */
/*   Updated: 2024/06/27 13:37:27 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_ceiling(t_game *game)
{
	size_t	x;
	size_t	y;

	game->floor_ceiling = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	x = 0;
	y = 0;
	while (y < game->floor_ceiling->height)
	{
		if (y < WINDOW_HEIGHT / 2)
			mlx_put_pixel(game->floor_ceiling, x, y, 0xFFFFFF);
		else
			mlx_put_pixel(game->floor_ceiling, x, y, 0xFFFFFF);
		if (++x >= game->floor_ceiling->width)
		{
			x = 0;
			y++;
		}
	}
}
