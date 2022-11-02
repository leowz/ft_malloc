/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:46:24 by zweng             #+#    #+#             */
/*   Updated: 2022/11/02 11:42:03 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *search_ptr(t_page **g_page, void *ptr)
{
    t_block *block;
    t_page  *page;

    block = NULL;
    page = *g_page;
    while (page)
    {
        block = (t_block *)PAGE_SHIFT(page);
        while (block)
        {
            if (BLOCK_SHIFT(block) == ptr)
            {
                *g_page = page;
                return (block);
            }
            block = block->next;
        }
        page = page->next;
    }
    *g_page = NULL;
    return (NULL);
}
