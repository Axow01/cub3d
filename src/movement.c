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
	if (key == MLX_KEY_W)
		if (at_pos(&game->map, game->player.px + game->player.pdx * 0.05, game->player.py + game->player.pdy * 0.05) != '1')
		{
			game->player.px += game->player.pdx * 0.05;
			game->player.py += game->player.pdy * 0.05;
		}
	if (key == MLX_KEY_S)
		if (at_pos(&game->map, game->player.px - game->player.pdx * 0.05, game->player.py - game->player.pdy * 0.05) != '1')
		{
			game->player.px -= game->player.pdx * 0.05;
			game->player.py -= game->player.pdy * 0.05;
		}
	if (key == MLX_KEY_A)
		if (at_pos(&game->map, game->player.px - game->player.planex * 0.05, game->player.py - game->player.planey * 0.05) != '1')
		{
			game->player.px -= game->player.planex * 0.05;
			game->player.py -= game->player.planey * 0.05;
		}
	if (key == MLX_KEY_D)
		if (at_pos(&game->map, game->player.px + game->player.planex * 0.05, game->player.py + game->player.planey * 0.05) != '1')
		{
			game->player.px += game->player.planex * 0.05;
			game->player.py += game->player.planey * 0.05;
		}
}


void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;
	bool		state;

	game = (t_game*)param;
	state = false;
	if (keydata.key == MLX_KEY_ESCAPE)
		mms_kill("Escaped!", true, 0);
	if (keydata.action == MLX_PRESS)
		state = true;
	else if (keydata.action == MLX_RELEASE)
		state = false;
	// Change to remove this if
	if (keydata.action == MLX_RELEASE || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			game->keystates.forward = state;
		else if (keydata.key == MLX_KEY_S)
			game->keystates.backward = state;
		else if (keydata.key == MLX_KEY_A)
			game->keystates.left = state;
		else if (keydata.key == MLX_KEY_D)
			game->keystates.right = state;
		else if (keydata.key == MLX_KEY_LEFT)
			game->keystates.rleft = state;
		else if (keydata.key == MLX_KEY_RIGHT)
			game->keystates.rright = state;
	}
}

// Fix so it doesnt move according to player fps
void	handle_movement(t_game *game)
{
	static double	last_update = 0;

	last_update += game->mlx->delta_time;
	if (last_update > 0.00001)
	{
		last_update = 0;
		if (game->keystates.forward)
			side_move(game, MLX_KEY_W);
		if (game->keystates.backward)
			side_move(game, MLX_KEY_S);
		if (game->keystates.right)
			side_move(game, MLX_KEY_D);
		if (game->keystates.left)
			side_move(game, MLX_KEY_A);
		if (game->keystates.rright)
			calculate_player_pos(game, MLX_KEY_RIGHT);
		if (game->keystates.rleft)
			calculate_player_pos(game, MLX_KEY_LEFT);
	}
}