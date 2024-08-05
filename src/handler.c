/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:11:38 by mmarcott          #+#    #+#             */
/*   Updated: 2024/08/05 11:18:33 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	check_states(mlx_key_data_t keydata, t_game *game)
{
	bool state;

	state = true;
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
