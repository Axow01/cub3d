/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:14:55 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/17 18:27:16 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_player	*init_player(t_game *game, float x, float y, char angle) 
{
	t_player	*player;

	(void)angle;
	player = &game->player;
	player->pAngle = 0;
	player->px = x;
	player->py = y;
	player->pdx = cos(player->pAngle) * 5;
	player->pdy = sin(player->pAngle) * 5;
	return (player);
}

// void	dda(t_game *game, t_player *player)
// {

// }

// void	raycast(t_game *game) {
// 	dda(game, &game->player);
// }