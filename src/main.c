/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:17:36 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/21 02:09:02 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	quitting_test(void *param)
{
	mlx_terminate((mlx_t *) ((t_game*)param)->mlx);
}

void	loop(void *param)
{
	t_game		*game;

	game = (t_game*)param;
	raycast(game);
}

int	main(int argc, char **argv) {
	struct mlx	*mlx;
	t_game		game;
	t_player	*player;

	if (argc != 2)
		return (0);
	ft_bzero(&game, sizeof(t_game));
	mms_set_alloc_fn(ft_calloc);
	if (!(mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false)))
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	mms_register_callback(quitting_test, &game);
	player = init_player(&game, 11, 1, 'N');
	game.mlx = mlx;
	if (!parse_file(&game, argv[1]))
		return (0);
	if (!initialize_minimap(&game))
		return (0);
	printf("Player x:%f y: %f\n", player->px, player->py);
	update_minimap(&game);
	game.wall = mlx_new_image(game.mlx, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
	mlx_key_hook(mlx, key_hook, &game);
	mlx_loop_hook(mlx, loop, &game);
	mlx_loop(mlx);
	mms_kill("", false, 0);
	return (0);
}
