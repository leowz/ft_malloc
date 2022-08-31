 ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:51:34 by zweng             #+#    #+#             */
/*   Updated: 2022/08/29 16:05:15 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


void    start_free(void *ptr)
{
    t_page  *g_page;
    t_block *blk;
    t_block *ret;

    page = g_malloc_page;
    if (!ptr || !page)
        return ;
    blk = search_ptr(&page, ptr);
    if (blk && page)
    {
       blk->freed = TRUE;
       ret = merge_block(page, blk);
       blk = ret ? ret : blk;
       remove_block_if_last(page, blk);
       delete_page_if_possible(page);
    }
}

void    free(void *ptr)
{
    pthread_mutex_lock(&g_malloc_mutex);
    start_free(ptr);
    pthread_mutex_unlock(&g_malloc_mutex);
}
