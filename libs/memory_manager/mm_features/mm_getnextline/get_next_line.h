/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 20:21:20 by tparadis          #+#    #+#             */
/*   Updated: 2024/05/12 17:16:01 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "../memory_manager/memory_manager.h"
# define BUFFER_SIZE 0x1000
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

char	*mu_gnl(int fd);
size_t	gnl_strlen(char *s);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
char	*gnl_strjoin(const char *s1, const char *s2);
char	*gnl_strdupn(char *s, size_t sz);
char	*gnl_realloc(char *current, char *buf);

#endif
