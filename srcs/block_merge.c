/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:05:58 by zweng             #+#    #+#             */
/*   Updated: 2022/08/31 16:01:22 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *merge_next_block(t_page *page, t_block *blk)
{
    if (page && blk && blk->next && blk->next->freed)
    {
       blk->size += blk->next->size + sizeof(t_block);
       if (blk->next && blk->next->next)
           blk->next->next->prev = blk;
       blk->next = blk->next->next;
       page->block_count--;
       return (blk);
    }
    return (NULL);
}

t_block *merge_prev_block(t_page *page, t_block *blk)
{
    if (page && blk && blk->prev && blk->prev->freed)
    {
        blk->prev->next = blk->next;
        if (blk->next)
            blk->next->prev = blk->prev;
        blk->prev->size += blk->size + sizeof(t_block);
        page->block_count--;
        return (blk->prev);
    }
    return (NULL);
}

t_block *merge_block(t_page *page, t_block *blk)
{
    if (merge_next_block(page, blk))
        return (merge_prev_block(page, blk));
    return (NULL);
}
