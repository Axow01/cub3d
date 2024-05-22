
#include "../includes/cub3d.h"

void	draw_floor_ceiling(t_game *game)
{
	size_t	x;
	size_t	y;

	game->floor_ceiling = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	x = 0;
	y = 0;
	while (y < game->floor_ceiling->height)
	{
		if (y < WINDOW_HEIGHT / 2)
			mlx_put_pixel(game->floor_ceiling, x, y, game->ceiling_color);
		else
			mlx_put_pixel(game->floor_ceiling, x, y, game->floor_color);
		if (++x >= game->floor_ceiling->width)
		{
			x = 0;
			y++;
		}
	}
	mlx_image_to_window(game->mlx, game->floor_ceiling, 0, 0);
}
