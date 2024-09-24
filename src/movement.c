/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:46:26 by mmarcott          #+#    #+#             */
/*   Updated: 2024/09/24 12:41:05 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_player_pos_left(t_game *game, keys_t key)
{
	t_player	*player;
	double		old_dir;
	double		old_plane;

	player = &game->player;
	if (key == MLX_KEY_RIGHT)
	{
		old_dir = player->pdx;
		player->pdx = player->pdx * cos(ROT_SPEED)
			- player->pdy * sin(ROT_SPEED);
		player->pdy = old_dir * sin(ROT_SPEED) + player->pdy * cos(ROT_SPEED);
		old_plane = player->planex;
		player->planex = player->planex * cos(ROT_SPEED)
			- player->planey * sin(ROT_SPEED);
		player->planey = old_plane * sin(ROT_SPEED)
			+ player->planey * cos(ROT_SPEED);
	}
}

void	calculate_player_pos(t_game *game, keys_t key)
{
	t_player	*player;
	double		old_dir;
	double		old_plane;

	player = &game->player;
	calculate_player_pos_left(game, key);
	if (key == MLX_KEY_LEFT)
	{
		old_dir = player->pdx;
		player->pdx = player->pdx * cos(-ROT_SPEED)
			- player->pdy * sin(-ROT_SPEED);
		player->pdy = old_dir * sin(-ROT_SPEED) + player->pdy * cos(-ROT_SPEED);
		old_plane = player->planex;
		player->planex = player->planex * cos(-ROT_SPEED)
			- player->planey * sin(-ROT_SPEED);
		player->planey = old_plane * sin(-ROT_SPEED)
			+ player->planey * cos(-ROT_SPEED);
	}
}

void	side_move_two(t_game *game, keys_t key)
{
	if (key == MLX_KEY_W)
	{
		if (at_pos(&game->map, game->player.px + game->player.pdx * 0.05,
				game->player.py + game->player.pdy * 0.05) != '1')
		{
			game->player.px += game->player.pdx * 0.05;
			game->player.py += game->player.pdy * 0.05;
		}
	}
	if (key == MLX_KEY_S)
	{
		if (at_pos(&game->map, game->player.px - game->player.pdx * 0.05,
				game->player.py - game->player.pdy * 0.05) != '1')
		{
			game->player.px -= game->player.pdx * 0.05;
			game->player.py -= game->player.pdy * 0.05;
		}
	}
}

void	side_move(t_game *game, keys_t key)
{
	side_move_two(game, key);
	if (key == MLX_KEY_A)
	{
		if (at_pos(&game->map, game->player.px - game->player.planex * 0.05,
				game->player.py - game->player.planey * 0.05) != '1')
		{
			game->player.px -= game->player.planex * 0.05;
			game->player.py -= game->player.planey * 0.05;
		}
	}
	if (key == MLX_KEY_D)
	{
		if (at_pos(&game->map, game->player.px + game->player.planex * 0.05,
				game->player.py + game->player.planey * 0.05) != '1')
		{
			game->player.px += game->player.planex * 0.05;
			game->player.py += game->player.planey * 0.05;
		}
	}
}

// check_states(keydata, game);
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;
	bool		state;

	game = (t_game *)param;
	state = false;
	if (keydata.key == MLX_KEY_ESCAPE)
		mms_kill("Escaped!\n", true, 0);
	if (keydata.action == MLX_PRESS)
		state = true;
	else if (keydata.action == MLX_RELEASE)
		state = false;
	calculate_player_pos(game, keydata.key);
	calculate_player_pos_left(game, keydata.key);
	side_move(game, keydata.key);
	side_move_two(game, keydata.key);
	if (state)
		state = true;
}
