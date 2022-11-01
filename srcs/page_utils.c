/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:27:47 by zweng             #+#    #+#             */
/*   Updated: 2022/11/01 22:01:23 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int     is_last_of_preallocated(t_page *page)
{
    t_page      *g_page;
    t_page_type type;
    int         i;

    g_page = g_malloc_page;
    type = page->type;
    if (type == LARGE)
        return (FALSE);
    i = 0;
    while (g_page)
    {
        if (g_page->type == type)
            i++;
        g_page = g_page->next;
    }
    return (i < 2);
}

void    delete_page_if_possible(t_page *page)
{
    if (page->block_count)
        return ;
    if (page->prev)
        page->prev->next = page->next;
    if (page->next)
        page->next->prev = page->prev;
    if (!is_last_of_preallocated(page))
    {
       if (page == g_malloc_page) 
           g_malloc_page = page->next;
       munmap(page, page->total_size);
    }
}

t_page  *get_last_page(t_page *page)
{
    if (!page)
        return (NULL);
    while (page->next)
        page = page->next;
    return (page);
}
