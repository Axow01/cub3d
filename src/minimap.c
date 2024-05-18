#include "cub3d.h"

bool	initialize_minimap(t_game *game)
{
	game->minimap.minimap_img = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!game->minimap.minimap_img)
		return (false);
	return (true);
}