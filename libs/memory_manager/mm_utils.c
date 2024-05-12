/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:10:42 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/12 20:38:00 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

void	*mm_memset(void *ptr, int value, size_t num)
{
	size_t	i;

	i = -1;
	while (++i < num)
		((unsigned char *)ptr)[i] = (unsigned char)value;
	return (ptr);
}

void	mm_bzero(void *s, size_t n)
{
	mm_memset(s, 0, n);
}

void	mm_print_all_nodes(t_memory_manager *instance)
{
	t_mm_node	*current_node;

	current_node = instance->alloc_list;
	while (current_node)
	{
		printf("Address : %p\n", current_node->allocation);
		current_node = current_node->next;
	}
}
