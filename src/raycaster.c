/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:14:55 by mmarcott          #+#    #+#             */
/*   Updated: 2024/07/05 19:25:43 by mmarcott         ###   ########.fr       */
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
	ray->side_dist_x = (ray->map_x + 1.0 - player->px) * ray->delta_dist_x;
	ray->side_dist_y = (ray->map_y + 1.0 - player->py) * ray->delta_dist_y;
	ray->step_x = 1;
	ray->step_y = 1;
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

	if (ray->side <= 1)
		wall_dist = (ray->map_x - player->px
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		wall_dist = (ray->map_y - player->py
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	return (wall_dist);
}

static void	dda(t_game *game, t_cast_result *cast, t_ray ray)
{
	init_ray(&ray, &game->player, cast->cam_x);
	while (true)
	{
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
			if (ray.step_x < 0)
				ray.side = 1;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
			ray.side = 2;
			if (ray.step_y < 0)
				ray.side = 3;
		}
		if (at_pos(&game->map, ray.map_x, ray.map_y) == '1')
			break ;
	}
	cast_setup(cast, game, ray);
}

void	cast_setup(t_cast_result *cast, t_game *game, t_ray ray)
{
	cast->map_x = ray.map_x;
	cast->map_y = ray.map_y;
	cast->distance = get_wall_dist(&ray, &game->player);
	cast->hit_x = game->player.px + cast->distance * ray.ray_dir_x;
	cast->hit_y = game->player.py + cast->distance * ray.ray_dir_y;
	cast->side = ray.side;
	cast->ray_dir_x = ray.ray_dir_x;
	cast->ray_dir_y = ray.ray_dir_y;
}

void	raycast(t_game *game, t_cast_result *cast)
{
	t_ray	ray;

	cast->cam_x = 2 * cast->cast_x / (double)WINDOW_WIDTH - 1;
	dda(game, cast);
}
