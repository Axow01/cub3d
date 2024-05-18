/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:46:26 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/17 18:46:09 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calculate_player_pos(t_player *player, keys_t key)
{
	if (key == MLX_KEY_A)
	{
		player->pAngle -= 0.1;
		if (player->pAngle < 0)
			player->pAngle += 2 * PI;
		player->pdx = cos(player->pAngle) * 5;
		player->pdy = sin(player->pAngle) * 5;
	}
	if (key == MLX_KEY_D)
	{
		player->pAngle += 0.1;
		if (player->pAngle > 0)
			player->pAngle -= 2 * PI;
		player->pdx = cos(player->pAngle) * 5;
		player->pdy = sin(player->pAngle) * 5;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param) {
	t_player	*player;

	player = (t_player*)param;
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
	calculate_player_pos(player, keydata.key);
}