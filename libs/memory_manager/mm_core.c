/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:47:16 by tparadis          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:37 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

t_memory_manager	*mm_get_instance()
{
	static t_memory_manager	*instance = NULL;

	if (!instance)
	{
		instance = malloc(sizeof(t_memory_manager));
		if (!instance)
			return (NULL);
		mm_bzero(instance, sizeof(t_memory_manager));
		instance->alloc_list = NULL;
		instance->callback = false;
	}
	return (instance);
}

void	mm_register_callback(void (*callback_func)(void *), void *param)
{
	t_memory_manager	*instance;

	instance = mm_get_instance();
	instance->callback = true;
	instance->callback_param = param;
	instance->exit_callback = callback_func;
}
