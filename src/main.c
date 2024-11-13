/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:17:36 by mmarcott          #+#    #+#             */
/*   Updated: 2024/11/12 14:41:30 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <time.h>

// void	get_fps(void)
// {
// 	static time_t		curr_time;
// 	static unsigned int	frames;

// 	curr_time = 0;
// 	frames = 0;
// 	if (!curr_time)
// 		curr_time = time(NULL);
// 	if (time(NULL) > curr_time)
// 	{
// 		printf("FRAMES: %u\n", frames);
// 		frames = 0;
// 		curr_time = time(NULL);
// 	}
// 	frames++;
// }

void	quitting_test(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mms_unregister_callback();
	mlx_delete_texture(game->no_texture);
	mlx_delete_texture(game->so_texture);
	mlx_delete_texture(game->we_texture);
	mlx_delete_texture(game->ea_texture);
	mlx_delete_image(game->mlx, game->wall);
	mlx_delete_image(game->mlx, game->floor_ceiling);
	mlx_terminate(game->mlx);
}

void	loop(void *param)
{
	t_game		*game;

	game = (t_game *)param;
	(void)game;
	draw_wall(game);
	handle_movement(game);
}

void	init_player_other_angle(t_player *player, char angle)
{
	if (angle == 'W')
	{
		player->pdx = -1.0;
		player->pdy = 0.0;
		player->planex = 0.0;
		player->planey = -0.66;
	}
	else if (angle == 'E')
	{
		player->pdx = 1.0;
		player->pdy = 0.0;
		player->planex = 0.0;
		player->planey = 0.66;
	}
}

void	init_player(t_player *player, float x, float y, char angle)
{
	player->initialized = true;
	player->px = x + 0.5;
	player->py = y + 0.5;
	if (angle == 'N')
	{
		player->pdx = 0.0;
		player->pdy = -1.0;
		player->planex = 0.66;
		player->planey = 0.0;
	}
	else if (angle == 'S')
	{
		player->pdx = 0.0;
		player->pdy = 1.0;
		player->planex = -0.66;
		player->planey = 0.0;
	}
	else
		init_player_other_angle(player, angle);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_game		game;

	if (argc != 2)
		return (puts("Error"), EXIT_FAILURE);
	ft_bzero(&game, sizeof(t_game));
	mms_set_alloc_fn(ft_calloc);
	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	if (!mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	game.mlx = mlx;
	if (!parse_file(&game, argv[1]))
		return (mms_kill("Error\n", true, 1), 1);
	mms_register_callback(quitting_test, &game);
	game.wall = mlx_new_image(game.mlx, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
	draw_floor_ceiling(&game);
	mlx_image_to_window(game.mlx, game.wall, 0, 0);
	mlx_key_hook(mlx, key_hook, &game);
	mlx_loop_hook(mlx, loop, &game);
	mlx_loop(game.mlx);
	mms_kill("Qutting without key!\n", false, 0);
	return (0);
}
