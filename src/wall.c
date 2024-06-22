#include "cub3d.h"
 

mlx_texture_t   *get_texture(t_game *game, t_cast_result *res)
{
    if (res->side == 3)
        return (game->so_texture);
    if (res->side == 2)
        return (game->no_texture);
    if (res->side == 1)
        return (game->we_texture);
    if (res->side == 0)
        return (game->ea_texture);
    printf("SIDE: %d, HIT_X: %f, HIT_Y: %f, MAPX: %d, MAPY: %d\n", res->side, res->hit_x, res->hit_y, res->map_x, res->map_y);
    return (game->no_texture);
}
/*
static void	draw_test_wall(t_game *game, int draw_start, int draw_end, int x)
{
	int			y;

	y = draw_start - 1;
	while (++y < draw_end)
	{
			if (y % 2)
				mlx_put_pixel(game->wall, x, y, 0x7d4777ff);
			else
				mlx_put_pixel(game->wall, x, y, 0x7d4777ff);

	}
}*/

static  void draw_sky_floor(t_game *game, int x, int draw_start, int draw_end)
{
    int y;

    y = 0;
    while (y < draw_start)
    {
		mlx_put_pixel(game->wall, x, y, game->ceiling_color);
        y++;
    }
    y = draw_end;
    while (y < WINDOW_HEIGHT)
    {
		mlx_put_pixel(game->wall, x, y, game->floor_color);
        y++;
    }
}

static void draw_line(t_game *game, t_cast_result *res, mlx_texture_t *texture, int x_index)
{
    int		line_height;
	int		draw_start;
	int		draw_end;
    double  step_size;
    double  wall_y;

    line_height = (int)(WINDOW_HEIGHT / res->distance);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
    step_size = 1.0 * texture->height / line_height;
    wall_y = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step_size;
    draw_sky_floor(game, res->cast_x, draw_start, draw_end);
    while (draw_start < draw_end)
    {
        wall_y += step_size;
        unsigned int color = ((unsigned int*)texture->pixels)[texture->height * ((int)wall_y & (texture->height - 1)) + x_index];
        mlx_put_pixel(game->wall, res->cast_x, draw_start, color);
        draw_start++;
    }
}

static void draw_texture(t_game *game, t_cast_result *res)
{
    double          wall_x;
    mlx_texture_t   *texture;
    int             x_index;

    texture = get_texture(game, res);
    wall_x = res->hit_y;
    if (res->side >= 2)
        wall_x = res->hit_x;
    wall_x -= (int)wall_x;
    x_index = (int)(wall_x * (double)texture->width);
    if ((res->side >= 2 && res->ray_dir_y < 0) || (res->side <= 1 && res->ray_dir_x > 0))
        x_index = texture->width - x_index - 1;
    draw_line(game, res, texture, x_index);
}   

void	draw_wall(t_game *game)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
    t_cast_result   cast;

	cast.cast_x = -1;
	ft_bzero(game->wall->pixels, game->wall->width * game->wall->height * sizeof(uint32_t));
	while (++cast.cast_x < WINDOW_WIDTH)
	{
		raycast(game, &cast);
		line_height = (int)(WINDOW_HEIGHT / cast.distance);
		draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;
		draw_texture(game, &cast);
	}
}
