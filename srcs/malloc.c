/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:44:04 by zweng             #+#    #+#             */
/*   Updated: 2022/11/02 11:39:46 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page		        *g_malloc_page = NULL;
pthread_mutex_t		g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void    *start_malloc(size_t size)
{
    t_block *block;

    if (!size)
        return (NULL);
    size = (size + 15) & ~15;
    if ((block = try_find_available_block(size)))
        return ((void *)BLOCK_SHIFT(block));
    else if ((block = try_create_new_block(size)))
        return ((void *)BLOCK_SHIFT(block));
    return (NULL);
}

void    *malloc(size_t size)
{
    void    *ptr;

    pthread_mutex_lock(&g_malloc_mutex);
    ptr = start_malloc(size);
    pthread_mutex_unlock(&g_malloc_mutex);
    return (ptr);
}
