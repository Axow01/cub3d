/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:46:26 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/22 02:16:24 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calculate_player_pos(t_game *game, keys_t key)
{
	t_player	*player;
	double		old_dir;
	double		old_plane;

	player = &game->player;
	if (key == MLX_KEY_LEFT)
	{
		old_dir = player->pdx;
		player->pdx = player->pdx * cos(ROT_SPEED) - player->pdy * sin(ROT_SPEED);
		player->pdy = old_dir * sin(ROT_SPEED) + player->pdy * cos(ROT_SPEED);
		old_plane = player->planex;
		player->planex = player->planex * cos(ROT_SPEED) - player->planey * sin(ROT_SPEED);
		player->planey = old_plane * sin(ROT_SPEED) + player->planey * cos(ROT_SPEED);
	}
	if (key == MLX_KEY_RIGHT)
	{
		old_dir = player->pdx;
		player->pdx = player->pdx * cos(-ROT_SPEED) - player->pdy * sin(-ROT_SPEED);
		player->pdy = old_dir * sin(-ROT_SPEED) + player->pdy * cos(-ROT_SPEED);
		old_plane = player->planex;
		player->planex = player->planex * cos(-ROT_SPEED) - player->planey * sin(-ROT_SPEED);
		player->planey = old_plane * sin(-ROT_SPEED) + player->planey * cos(-ROT_SPEED);
	}
}

static void	side_move(t_game *game, keys_t key)
{
	if (key == MLX_KEY_A)
	{
		if (at_pos(&game->map, game->player.px - game->player.planex * 0.05, game->player.py - game->player.planey * 0.05) != '1')
		{
			game->player.px -= game->player.planex * 0.05;
			game->player.py -= game->player.planey * 0.05;
		}
	}
	if (key == MLX_KEY_D)
	{
		if (at_pos(&game->map, game->player.px + game->player.planex * 0.05, game->player.py + game->player.planey * 0.05) != '1')
		{
			game->player.px += game->player.planex * 0.05;
			game->player.py += game->player.planey * 0.05;
		}
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
		if (at_pos(&game->map, player->px + player->pdx * 0.05, player->py + player->pdy * 0.05) != '1')
		{
			player->px += player->pdx * 0.05;
			player->py += player->pdy * 0.05;
		}
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (at_pos(&game->map, player->px - player->pdx * 0.05, player->py - player->pdy * 0.05) != '1')
		{
			player->px -= player->pdx * 0.05;
			player->py -= player->pdy * 0.05;
		}
	}
	calculate_player_pos(game, keydata.key);
	side_move(game, keydata.key);
}
