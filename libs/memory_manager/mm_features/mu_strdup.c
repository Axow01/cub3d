/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mu_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:53:54 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/11 21:53:57 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_utils.h"

char	*mu_strdup(const char *str)
{
	size_t	strsz;
	char	*buf;

	strsz = mu_strlen(str);
	buf = mm_alloc(strsz + 1);
	if (!buf)
		return (0);
	mu_strlcpy(buf, str, strsz + 1);
	return (buf);
}
