/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_block_if_last.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:20:36 by zweng             #+#    #+#             */
/*   Updated: 2022/08/31 11:25:58 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    remove_block_if_last(t_page *page, t_block *block)
{
    if (block->freed && !block->next)
    {
        if (block->prev)
            block->prev->next = NULL;
        page->free_size += block->size + sizeof(t_block);
        page->block_count--;
    }
}
