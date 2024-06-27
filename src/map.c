/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:46:19 by mmarcott          #+#    #+#             */
/*   Updated: 2024/06/27 13:46:32 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Returns char at positon NULL if out of bounds
char	at_pos(t_map *map, size_t x, size_t y)
{
	if (y >= map->size)
		return (0);
	if (x >= map->grid[y].size)
		return (0);
	return (map->grid[y].line[x]);
}

void	set_pos(t_map *map, size_t x, size_t y, char val)
{
	if (y >= map->size)
		return ;
	if (x >= map->grid[y].size)
		return ;
	map->grid[y].line[x] = val;
}
