/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mu_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:54:24 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/15 16:36:26 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_utils.h"

static size_t	get_buf_size(char const *str, char c)
{
	size_t	i;
	size_t	last;
	size_t	result;

	i = 0;
	last = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (i - last > 1 || (!last && i))
				result++;
			last = i;
		}
		i++;
	}
	if ((i && last != i - 1) || (i && !last))
		result++;
	return (result + 1);
}

static char	*copy_string(const char *s, char c)
{
	char	*next;
	size_t	len;

	next = mu_strchr(s, c);
	if (!next)
		return (mu_strdup(s));
	len = next - s;
	return (mu_substr(s, 0, len));
}

char	**mu_split(char const *s, char c)
{
	int		i;
	char	**ret;
	int		j;
	int		last;

	if (!s)
		return (NULL);
	ret = mm_alloc(sizeof(char *) * (get_buf_size(s, c)));
	i = 0;
	j = 0;
	last = 0;
	while (s[i])
	{
		if (((i - last == 0 && !last) || (i - last == 1 && last)
				|| (i - last == 1 && s[last] == c)) && s[i] != c)
			ret[j++] = copy_string(&s[i], c);
		if (s[i] == c)
			last = i;
		i++;
	}
	ret[j] = NULL;
	return (ret);
}
