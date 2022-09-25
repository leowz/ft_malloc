/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagrant </var/mail/vagrant>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:54:02 by vagrant           #+#    #+#             */
/*   Updated: 2022/09/25 21:44:17 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t  print_block_list(t_block *block)
{
    char    *start_address;
    char    *end_address;
    size_t  total;

    total = 0;
    start_address = NULL;
    end_address = NULL;
    while (block)
    {
       start_address = (char *)BLOCK_SHIFT(block);
       end_address = start_address + block->size;
       if (!block->freed)
       {
          ft_printf("0x%08x - 0x%08x : %d octets\n",
                  (size_t)start_address, (size_t)end_address, block->size);
          total += block->size;
       }
       block = block->next;
    }
    return (total);
}

void    start_show_alloc_mem(void)
{
    t_page  *page;
    t_page  *last_page;
    size_t  total;

    total = 0;
    page = g_malloc_page;
    last_page = get_last_page(page);
    while (last_page)
    {
       if (last_page->type == TINY) 
           ft_printf("%s : 0x%08x\n", "TINY", (size_t)last_page);
       else if (last_page->type == SMALL)
           ft_printf("%s : 0x%08x\n", "SMALL", (size_t)last_page);
       else
           ft_printf("%s : 0x%08x\n", "LARGE", (size_t)last_page);
       if (last_page->block_count)
           total += print_block_list((t_block *)PAGE_SHIFT(last_page));
       last_page = last_page->prev;
    }
    ft_printf("Total : %d octets\n", total);
}

void    show_alloc_mem(void)
{
    pthread_mutex_lock(&g_malloc_mutex);
    start_show_alloc_mem();
    pthread_mutex_unlock(&g_malloc_mutex);
}
