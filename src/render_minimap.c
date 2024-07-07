#include "cub3d.h"

// void	draw_tile()
// {
	
// }

void	draw_minimap_background(t_game *game)
{
	ft_memset(game->minimap.minimap_img->pixels, 255, MINIMAP_SIZE * MINIMAP_SIZE * sizeof(int));
	mlx_image_to_window(game->mlx, game->minimap.minimap_img, WINDOW_WIDTH - MINIMAP_SIZE, WINDOW_HEIGHT - MINIMAP_SIZE);
}

// void	draw_minimap_player()
// {

// }

void	update_minimap(t_game *game)
{
	draw_minimap_background(game);
}
