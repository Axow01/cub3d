/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:09:59 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/11 21:39:39 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

// Function called to clean up. is not 
// called externally therefore doesnt callback
void	mm_exit()
{
	t_mm_node	*current_node;
	void		*address;
	t_memory_manager *instance;

	instance = mm_get_instance();
	current_node = instance->alloc_list;
	while (current_node)
	{
		address = current_node->allocation;
		current_node = current_node->next;
		mm_free(address);
	}
	free(instance);
	exit(EXIT_SUCCESS);
}

// Function called when a malloc fail or any other error occurs
void	mm_fast_exit()
{
	t_mm_node	*current_node;
	void		*address;
	t_memory_manager *instance;

	instance = mm_get_instance();
	if (instance->callback)
		instance->exit_callback(instance->callback_param);
	current_node = instance->alloc_list;
	while (current_node)
	{
		address = current_node->allocation;
		current_node = current_node->next;
		mm_free(address);
	}
	free(instance);
	exit(EXIT_FAILURE);
}
