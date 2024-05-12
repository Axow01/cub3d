/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:19:58 by tparadis          #+#    #+#             */
/*   Updated: 2023/05/26 19:19:15 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (gnl_strlen((char *)src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (gnl_strlen((char *)src));
}

char	*gnl_strjoin(const char *s1, const char *s2)
{
	size_t	sz1;
	size_t	sz2;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	sz1 = gnl_strlen((char *)s1);
	sz2 = gnl_strlen((char *)s2);
	ret = mm_alloc(sizeof(char) * (sz2 + sz1 + 1));
	if (!ret)
		return (NULL);
	gnl_strlcpy(ret, s1, sz1 + 1);
	gnl_strlcpy(ret + sz1, s2, sz2 + 1);
	return (ret);
}

char	*gnl_strdupn(char *s, size_t sz)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	if (sz)
		ret = mm_alloc(sizeof(char) * (sz + 1));
	else
		ret = mm_alloc(sizeof(char) * (gnl_strlen(s) + 1));
	if (!ret)
		return (NULL);
	while (s[i] && (i < sz - 1 || !sz))
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*gnl_realloc(char *current, char *buf)
{
	char	*ret;

	if (!current)
		ret = gnl_strjoin("", buf);
	else
	{
		ret = gnl_strjoin(current, buf);
		mm_free(current);
	}
	return (ret);
}
