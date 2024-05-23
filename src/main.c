/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:17:36 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/22 02:17:43 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include <time.h>

void	get_fps()
{
	static	time_t curr_time = 0;
	static	unsigned int frames = 0;

	if (!curr_time)
		curr_time = time(NULL);
	if (time(NULL) > curr_time)
	{
		printf("FRAMES: %u\n", frames);
		frames = 0;
	}
	frames++;
	curr_time = time(NULL);
	
}

void	quitting_test(void *param)
{
	//mlx_delete_image(((t_game*)param)->mlx,((t_game*)param)->floor_ceiling);
	mlx_terminate((mlx_t *) ((t_game*)param)->mlx);
}

void	loop(void *param)
{
	t_game		*game;

	game = (t_game*)param;
	raycast(game);
	get_fps();
}

void	init_player(t_player *player, float x, float y, char angle) 
{
	(void)angle;
	player->px = x + 0.5;
	player->py = y + 0.5;
	player->pdx = -1.0;
	player->pdy = 0.0;
	player->planex = 0.0;
	player->planey = 0.66;
}

int	main(int argc, char **argv) {
	struct mlx	*mlx;
	t_game		game;

	if (argc != 2)
		return (0);
	ft_bzero(&game, sizeof(t_game));
	mms_set_alloc_fn(ft_calloc);
	if (!(mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false)))
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	mms_register_callback(quitting_test, &game);
	game.mlx = mlx;
	if (!parse_file(&game, argv[1]))
		return (0);
	if (!initialize_minimap(&game))
		return (0);
	printf("Player x:%f y: %f\n", game.player.px, game.player.py);
	update_minimap(&game);
	game.wall = mlx_new_image(game.mlx, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
	game.no_texture = mlx_load_png("wall3.png");
	draw_floor_ceiling(&game);
	printf("Ceiling: %x Floor: %x\n", game.ceiling_color, game.floor_color);
	mlx_key_hook(mlx, key_hook, &game);
	mlx_loop_hook(mlx, loop, &game);
	mlx_loop(mlx);
	mms_kill("", false, 0);
	return (0);
}
