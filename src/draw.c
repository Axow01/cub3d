/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:36:42 by mmarcott          #+#    #+#             */
/*   Updated: 2024/10/22 14:11:56 by mmarcott         ###   ########.fr       */
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

mlx_texture_t	*get_texture(t_game *game, t_cast_result *res)
{
	if (res->side == 3)
		return (game->no_texture);
	if (res->side == 2)
		return (game->so_texture);
	if (res->side == 1)
		return (game->we_texture);
	if (res->side == 0)
		return (game->ea_texture);
	printf("SIDE: %d, HIT_X: %f, HIT_Y: %f, MAPX: %d, MAPY: %d\n",
		res->side, res->hit_x, res->hit_y, res->map_x, res->map_y);
	return (game->no_texture);
}

void	setup_line(t_linedraw *line, mlx_texture_t *texture, t_cast_result *res)
{
	line->line_height = (int)(WINDOW_HEIGHT / res->distance);
	line->draw_start = -line->line_height / 2 + WINDOW_HEIGHT / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->line_height / 2 + WINDOW_HEIGHT / 2;
	if (line->draw_end >= WINDOW_HEIGHT)
		line->draw_end = WINDOW_HEIGHT - 1;
	line->step_size = 1.0 * texture->height / line->line_height;
	line->wall_y = (line->draw_start
			- WINDOW_HEIGHT / 2 + line->line_height / 2) * line->step_size;
}
