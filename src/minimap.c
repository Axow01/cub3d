/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:48:12 by mmarcott          #+#    #+#             */
/*   Updated: 2024/06/27 13:48:15 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	initialize_minimap(t_game *game)
{
	game->minimap.minimap_img
		= mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!game->minimap.minimap_img)
		return (false);
	return (true);
}
