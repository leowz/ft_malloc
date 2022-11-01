/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_create_new_block.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:55:38 by zweng             #+#    #+#             */
/*   Updated: 2022/11/01 22:02:12 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

size_t  get_page_size_from_block_type(t_page_type type, size_t size)
{
    if (type == TINY)
        return ((size_t)TINY_ZONE);
    else if (type == SMALL)
        return ((size_t)SMALL_ZONE);
    else 
        return (size + sizeof(t_page) + sizeof(t_block));
}

static rlim_t	get_system_limit(void)
{
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return (-1);
	return (rpl.rlim_max);
}

t_page  *create_page(t_page_type type, size_t block_size)
{
    size_t  size;
    t_page  *page; 

    size = get_page_size_from_block_type(type, block_size);
    if (size > get_system_limit())
        return (NULL);
    if ((page = (t_page *)mmap(NULL, size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
        return (NULL);
    ft_bzero(page, sizeof(t_page));
    page->type = type;
    page->total_size = size;
    page->free_size = size - sizeof(t_page);
    return (page);
}

t_page  *get_available_page(t_page *page, t_page_type type, size_t size)
{
    t_page  *page_candidate;

    page_candidate = page;
    while (page_candidate)
    {
       if ((page_candidate->type == type) && page_candidate->free_size >= size) 
           return (page_candidate);
       page_candidate = page_candidate->next;
    }
    return (NULL);
}

t_page  *get_page_of_block_size(size_t size)
{
    t_page			*g_page;
	t_page			*page;
	t_page_type	    type;

	g_page = g_malloc_page;
	type = get_page_type(size);
	page = get_available_page(g_page, type, size + sizeof(t_block));
	if (page == NULL)
	{
		if (!(page = create_page(type, size)))
			return (NULL);
		page->next = (t_page *)g_page;
		if (page->next)
			page->next->prev = page;
		g_malloc_page = page;
	}
	return (page);
}

t_block *get_last_block(t_block *blk)
{
    while (blk->next)
        blk = blk->next;
    return (blk);
}

t_block *create_append_new_block(t_page *page, size_t size)
{
    t_block *new_blk;
    t_block *last_blk;

    last_blk = NULL;
    new_blk = (t_block *)PAGE_SHIFT(page);
    if (page->block_count && (last_blk = get_last_block(new_blk)))
    {
        new_blk = (void *)(BLOCK_SHIFT(last_blk) + last_blk->size);
    }
    set_block(new_blk, size);
    if (page->block_count && last_blk)
        insert_block(last_blk, new_blk);
    page->block_count++;
    page->free_size -= (new_blk->size + sizeof(t_block));
    return (new_blk);
}

t_block *try_create_new_block(size_t size)
{
    t_page  *page;
    t_block *block;

    if ((page = get_page_of_block_size(size)) &&
            (block = create_append_new_block(page, size)))
        return (block);
    return (NULL);
}
