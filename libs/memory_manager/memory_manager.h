/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparadis <tparadis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:15:58 by tparadis          #+#    #+#             */
/*   Updated: 2024/01/11 21:34:43 by tparadis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGER_H
# define MEMORY_MANAGER_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_mm_node
{
	struct s_mm_node	*next;
	void				*allocation;
}						t_mm_node;

typedef struct s_memory_manager
{
	bool				callback;
	t_mm_node			*alloc_list;
	void				(*exit_callback)(void *);
	void				*callback_param;
}						t_memory_manager;


// INIT AND EXIT

void					mm_exit();
t_memory_manager		*mm_get_instance();
void					mm_register_callback(void (*callback_func)(void *),
							void *param);


// BASIC ALLOCATION FUNCTIONS

void					*mm_free(void *address);
void					*mm_alloc(size_t size);
void					*mm_calloc(size_t num, size_t size);

// SPECIAL ALLOCATIONS

void					*mm_register_alloc(void *address);
void					*mm_unregister_alloc(void *address);

// INTERNAL FUNCTIONS


t_memory_manager		*mm_get_instance();
t_mm_node				*mm_create_push_node();
void					mm_delete_node(t_mm_node *node);
t_mm_node				*mm_get_node_from_address(void *address);
void					mm_fast_exit();

// UTILS

void					mm_bzero(void *s, size_t n);


#endif