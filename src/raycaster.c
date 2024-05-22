/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:14:55 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/22 02:24:40 by mmarcott         ###   ########.fr       */
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

static void	draw_test_wall(int draw_start, int draw_end, t_game *game, int x)
{
	int			y;

	y = draw_start - 1;
	while (++y < draw_end)
	{
		if (!(y > WINDOW_HEIGHT - MINIMAP_SIZE && x > WINDOW_WIDTH - MINIMAP_SIZE))
			mlx_put_pixel(game->wall, x, y, 0x7CB342);
	}
}

void	raycast(t_game *game) {
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		x;
	double	wal_dist;
	double	camx;

	x = -1;
	ft_bzero(game->wall->pixels, game->wall->width * game->wall->height * sizeof(uint32_t));
	while (++x < WINDOW_WIDTH)
	{
		camx = 2 * x / (double)WINDOW_WIDTH - 1;
		wal_dist = dda(game, camx);
		line_height = (int)(WINDOW_HEIGHT / wal_dist);
		draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;
		draw_test_wall(draw_start, draw_end, game, x);
	}
	mlx_image_to_window(game->mlx, game->wall, 0, 0);
}
