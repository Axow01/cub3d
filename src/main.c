/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:17:36 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/13 01:58:18 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void) {
	struct mlx	*mlx;

	if (!(mlx = mlx_init(900, 800, "Cub3d", false)))
		return (puts(mlx_errno), EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
