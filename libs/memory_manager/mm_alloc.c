/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:47:21 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/11 21:55:12 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

void	*mm_free(void *address)
{
	t_mm_node	*node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	if (!address)
		return (NULL);
	node = mm_get_node_from_address(address);
	if (!node)
		return (NULL);
	free(node->allocation);
	mm_delete_node(node);
	return (NULL);
}

void	*mm_alloc(size_t size)
{
	t_mm_node			*node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	node = mm_create_push_node(instance);
	if (!node)
	{
		mm_fast_exit(instance);
		return (NULL);
	}
	node->allocation = malloc(size);
	if (!node->allocation)
	{
		mm_fast_exit(instance);
		return (NULL);
	}
	return (node->allocation);
}

void	*mm_calloc(size_t num, size_t size)
{
	void				*alloc;

	alloc = mm_alloc(size);
	if (alloc)
		mm_bzero(alloc, size);
	return (alloc);
}

void	*mm_register_alloc(void *address)
{
	t_mm_node			*node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	if (!address || !instance)
		return (NULL);
	node = mm_create_push_node(instance);
	if (!node)
	{
		mm_fast_exit(instance);
		return (NULL);
	}
	node->allocation = address;
	return (node->allocation);
}

void	*mm_unregister_alloc(void *address)
{
	t_mm_node	*node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	if (!address)
		return (NULL);
	node = mm_get_node_from_address(address);
	if (!node)
		return (NULL);
	mm_delete_node(node);
	return (NULL);
}
