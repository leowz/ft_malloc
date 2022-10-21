/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagrant </var/mail/vagrant>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:54:02 by vagrant           #+#    #+#             */
/*   Updated: 2022/10/21 18:49:14 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    print_range(t_block *block, char *start, char *end)
{
    ft_putstr("0x");
    ft_itoa_base((size_t)start, 16);
    ft_putstr(" - ");
    ft_putstr("0x");
    ft_itoa_base((size_t)end, 16);
    ft_putstr(" : ");
    ft_itoa_base(block->size, 10);
    ft_putstr(" octets\n");
}

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
           print_range(block, start_address, end_address);
           total += block->size;
       }
       block = block->next;
    }
    return (total);
}

void    print_header(char *name, t_page *page)
{
    ft_putstr(name);
	ft_putstr(" : 0x");
    ft_itoa_base((size_t)page, 16);
	ft_putstr("\n");
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
           print_header("TINY", last_page);
       else if (last_page->type == SMALL)
           print_header("SMALL", last_page);
       else
           print_header("LARGE", last_page);
       if (last_page->block_count)
           total += print_block_list((t_block *)PAGE_SHIFT(last_page));
       last_page = last_page->prev;
    }
    ft_putstr("Total : ");
	ft_itoa_base(total, 10);
	ft_putstr(" octets\n");
}

void    show_alloc_mem(void)
{
    pthread_mutex_lock(&g_malloc_mutex);
    start_show_alloc_mem();
    pthread_mutex_unlock(&g_malloc_mutex);
}
