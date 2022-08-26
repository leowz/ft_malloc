/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_find_available_block.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:26:38 by zweng             #+#    #+#             */
/*   Updated: 2022/08/25 15:09:34 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    set_block(t_block *blk, size_t size)
{
    blk->prev = NULL;
    blk->next = NULL;
    blk->size = size;
    blk->freed = FALSE;
}

t_block *set_block_safe(t_block *blk, size_t size, size_t old_size)
{
    if (size < old_size - sizeof(t_block))
    {
        set_block(blk, size);
        return (blk);
    }
    return (NULL);
}

void    insert_block(t_block *blk, t_block *blk_insert)
{
    blk_insert->next = blk->next;
    blk_insert->prev = blk;
    blk->next = blk_insert;
}

void    divide_block(t_block *blk, t_page *page, size_t size)
{
    t_block *new_block;
    t_block *block;

    new_block = BLOCK_SHIFT(blk) + size;
    if ((block = set_block_safe(new_block, blk->next - new_block, blk->size)))
    {
        block->freed = TRUE;
        insert_block(blk, block);
        page->block_count++;
        blk->size = size;
        blk->freed = FALSE;
    }
}

t_block *try_find_available_block(size_t size)
{
    t_block *block;
    t_page  *page;

    page = NULL;
    if ((block = find_available_block(size, &page)) && page)
    {
       divide_block(block, page, size);
       return (block);
    }
    return (NULL);
}
