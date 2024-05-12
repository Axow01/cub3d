/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:17:36 by mmarcott          #+#    #+#             */
/*   Updated: 2024/05/08 23:13:35 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void) {
	mms_set_alloc_fn(ft_calloc);
	char	*test = mms_alloc(25, sizeof(char));

	for (size_t i = 0; i < 25; i++) {
		test[i] = 'a';
	}
	ft_printf("STR: %s\n", test);
	mms_kill("", false, 0);
	return (0);
}
