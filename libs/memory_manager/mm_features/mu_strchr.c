/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mu_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:54:05 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/11 21:54:08 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_utils.h"

char	*mu_strchr(const char *str, int c)
{
	int				i;
	unsigned char	check;

	i = 0;
	check = c;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == check)
			return (((char *)str) + i);
		i++;
	}
	if (str[i] == check)
		return (((char *)str) + i);
	return (NULL);
}
