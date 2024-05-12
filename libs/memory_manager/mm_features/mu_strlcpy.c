/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mu_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:53:46 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/11 21:53:47 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_utils.h"

size_t	mu_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
		return (0);
	if (!size)
		return (mu_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (mu_strlen(src));
}
