/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_available_block.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:40:12 by zweng             #+#    #+#             */
/*   Updated: 2022/08/25 15:28:08 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page_type get_page_type(size_t size)
{
    if (size <= (size_t)TINY_BLOCK)
        return (TINY);
    else if (size <= (size_t)SMALL_BLOCK)
        return (SMALL);
    else
        return (LARGE);
}

t_block *find_available_block(size_t size, t_page **page)
{
    t_block     *block;
    t_page      *g_page;
    t_page_type page_type;

    g_page = g_malloc_page;
    page_type = get_page_type(size);
    while (g_page)
    {
       block = (t_block *)PAGE_SHIFT(g_page);
       while (g_page->type == page_type && block)
       {
           if (block->freed && (block->size >= size + sizeof(t_block)))
           {
               *page = g_page;
               return (block);
           }
           block = block->next;
       }
       g_page = g_page->next;
    }
    *page = NULL;
    return (NULL);
}
