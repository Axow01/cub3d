/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mu_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:52:40 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/11 21:52:49 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_utils.h"

char	*mu_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	sz;

	sz = mu_strlen(s);
	if (sz < len)
		len = sz;
	ret = mm_alloc(len + 1);
	if (!ret)
		return (NULL);
	if (start > mu_strlen(s))
		start = mu_strlen(s);
	mu_strlcpy(ret, s + start, len + 1);
	return (ret);
}
