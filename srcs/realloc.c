/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:04:03 by zweng             #+#    #+#             */
/*   Updated: 2022/09/23 18:55:57 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *start_realloc(void *ptr, size_t size)
{
    t_page  *g_page;
    t_block *block;
    void    *new_ptr;

    g_page = g_malloc_page;
    if (!ptr)
        return (start_malloc(size));
    else if (size == 0)
    {
       start_free(ptr);
       return (NULL);
    }
    if (!(block = search_ptr(&g_page, ptr)) || !g_page)
        return (NULL);
    else if (size == block->size)
        return (ptr);
    else
    {
        new_ptr = start_malloc(size);
        ft_memmove(new_ptr, ptr,
                block->size > size ? size : block->size);
        start_free(ptr);
        return (new_ptr);
    }
}

void    *ft_realloc(void *ptr, size_t size)
{
    void    *res;

    pthread_mutex_lock(&g_malloc_mutex);
    res = start_realloc(ptr, size);
    pthread_mutex_unlock(&g_malloc_mutex);
    return (res);
}
