/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_node_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:29:07 by tparadis          #+#    #+#             */
/*   Updated: 2023/05/25 20:21:46 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

t_mm_node	*mm_get_last_node()
{
	t_mm_node			*current_node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	current_node = instance->alloc_list;
	if (!current_node)
		return (NULL);
	while (current_node->next)
		current_node = current_node->next;
	return (current_node);
}

void	mm_delete_node(t_mm_node *node)
{
	t_mm_node			*current_node;
	t_mm_node			*last_node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	last_node = NULL;
	current_node = instance->alloc_list;
	while (current_node)
	{
		if (current_node == node)
		{
			if (last_node == NULL)
				instance->alloc_list = node->next;
			else
				last_node->next = current_node->next;
			free(node);
			return ;
		}
		last_node = current_node;
		current_node = current_node->next;
	}
}

t_mm_node	*mm_create_push_node()
{
	t_mm_node			*new_node;
	t_mm_node			*last_node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	new_node = malloc(sizeof(t_mm_node));
	if (!new_node)
	{
		if (instance->exit_on_fail)
			mm_fast_exit(instance);
		return (NULL);
	}
	mm_bzero(new_node, sizeof(t_mm_node));
	new_node->next = NULL;
	new_node->allocation = NULL;
	last_node = mm_get_last_node(instance);
	if (!last_node)
		instance->alloc_list = new_node;
	else
		last_node->next = new_node;
	return (new_node);
}

t_mm_node	*mm_get_node_from_address(void *address)
{
	t_mm_node			*current_node;
	t_memory_manager	*instance;

	instance = mm_get_instance();
	current_node = instance->alloc_list;
	if (!current_node)
		return (NULL);
	while (current_node->next)
	{
		if (current_node->allocation == address)
			break ;
		current_node = current_node->next;
	}
	return (current_node);
}
