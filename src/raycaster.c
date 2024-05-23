/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:14:55 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/23 00:32:37 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_ray(t_ray *ray, t_player *player, double camx)
{
	ray->map_x = (int)player->px;
	ray->map_y = (int)player->py;
	ray->ray_dir_x = player->pdx + player->planex * camx;
	ray->ray_dir_y = player->pdy + player->planey * camx;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->step_x = 1;
	ray->side_dist_x = (ray->map_x + 1.0 - player->px) * ray->delta_dist_x;
	ray->step_y = 1;
	ray->side_dist_y = (ray->map_y + 1.0 - player->py) * ray->delta_dist_y;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->px - ray->map_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->py - ray->map_y) * ray->delta_dist_y;
	}
}

static double	get_wall_dist(t_ray *ray, t_player *player)
{
	double	wall_dist;

	if (ray->side == 0)
		wall_dist = (ray->map_x - player->px + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		wall_dist = (ray->map_y - player->py + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	return (wall_dist);
}

static double	dda(t_game *game, double camx)
{
	t_ray	ray;
	bool	hit;

	init_ray(&ray, &game->player, camx);
	hit = false;
	while (!hit)
	{
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (at_pos(&game->map, ray.map_x, ray.map_y) == '1')
			hit = true;
	}
	return (get_wall_dist(&ray, &game->player));
}

static void	draw_test_wall(t_wall *wall, t_game *game)
{
	int			y;

	y = wall->start - 1;
	while (++y < wall->end)
	{
		if (!(y > WINDOW_HEIGHT - MINIMAP_SIZE && wall->x > WINDOW_WIDTH - MINIMAP_SIZE))
			mlx_put_pixel(game->wall, wall->x, y, 255);
	}
}

void	raycast(t_game *game) {
	t_wall	wall;

	wall.x = -1;
	ft_bzero(game->wall->pixels, game->wall->width * game->wall->height * sizeof(uint32_t));
	while (++wall.x < WINDOW_WIDTH)
	{
		wall.camera = 2 * wall.x / (double)WINDOW_WIDTH - 1;
		wall.distance = dda(game, wall.camera);
		wall.height = (int)(WINDOW_HEIGHT / wall.distance);
		wall.start = -wall.height / 2 + WINDOW_HEIGHT / 2;
		if (wall.start < 0)
			wall.start = 0;
		wall.end = wall.height / 2 + WINDOW_HEIGHT / 2;
		if (wall.end >= WINDOW_HEIGHT)
			wall.end = WINDOW_HEIGHT - 1;
		draw_test_wall(&wall, game);
	}
}
