/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:27:30 by tparadis          #+#    #+#             */
/*   Updated: 2024/05/12 17:15:07 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM_UTILS_H
# define MM_UTILS_H

# include "../memory_manager.h"

char	**mu_split(char const *s, char c);
char	*mu_strchr(const char *str, int c);
char	*mu_strdup(const char *str);
size_t	mu_strlcpy(char *dst, const char *src, size_t size);
size_t	mu_strlen(const char *str);
char	*mu_substr(char const *s, unsigned int start, size_t len);
char	*mu_gnl(int fd);


#endif