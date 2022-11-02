/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:51:34 by zweng             #+#    #+#             */
/*   Updated: 2022/11/02 11:39:52 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    start_free(void *ptr)
{
    t_page  *g_page;
    t_block *blk;
    t_block *ret;

    g_page = g_malloc_page;
    if (!ptr || !g_page)
        return ;
    blk = search_ptr(&g_page, ptr);
    if (blk && g_page)
    {
       blk->freed = TRUE;
       ret = merge_block(g_page, blk);
       blk = ret ? ret : blk;
       remove_block_if_last(g_page, blk);
       delete_page_if_possible(g_page);
    }
}

void    free(void *ptr)
{
    pthread_mutex_lock(&g_malloc_mutex);
    start_free(ptr);
    pthread_mutex_unlock(&g_malloc_mutex);
}
