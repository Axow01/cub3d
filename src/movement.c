/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:46:26 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/21 02:17:13 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calculate_player_pos(t_game *game, keys_t key)
{
	t_player	*player;
	double		old_dir;
	double		old_plane;

	player = &game->player;
	if (key == MLX_KEY_R)
		raycast(game);
	if (key == MLX_KEY_A)
	{
		old_dir = player->pdx;
		player->pdx = player->pdx * cos(ROT_SPEED) - player->pdy * sin(ROT_SPEED);
		player->pdy = old_dir * sin(ROT_SPEED) + player->pdy * cos(ROT_SPEED);
		old_plane = player->planex;
		player->planex = player->planex * cos(ROT_SPEED) - player->planey * sin(ROT_SPEED);
		player->planey = old_plane * sin(ROT_SPEED) + player->planey * cos(ROT_SPEED);
	}
	if (key == MLX_KEY_D)
	{
		old_dir = player->pdx;
		player->pdx = player->pdx * cos(-ROT_SPEED) - player->pdy * sin(-ROT_SPEED);
		player->pdy = old_dir * sin(-ROT_SPEED) + player->pdy * cos(-ROT_SPEED);
		old_plane = player->planex;
		player->planex = player->planex * cos(-ROT_SPEED) - player->planey * sin(-ROT_SPEED);
		player->planey = old_plane * sin(-ROT_SPEED) + player->planey * cos(-ROT_SPEED);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param) {
	t_player	*player;
	t_game		*game;

	game = (t_game*)param;
	player = &game->player;
	if (keydata.key == MLX_KEY_ESCAPE)
		mms_kill("Escaped!", true, 0);
	if (keydata.key == MLX_KEY_W)
	{
		player->px += player->pdx;
		player->py += player->pdy;
	}
	if (keydata.key == MLX_KEY_S)
	{
		player->px -= player->pdx;
		player->py -= player->pdy;
	}
	calculate_player_pos(game, keydata.key);
}
