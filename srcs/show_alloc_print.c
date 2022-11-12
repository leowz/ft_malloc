/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:47:42 by zweng             #+#    #+#             */
/*   Updated: 2022/11/12 13:48:42 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int    print_graph_blk(t_block *blk)
{
    size_t  size;
    size_t  i;
    char    chr;

    i = sizeof(t_block);
    size = blk->size + sizeof(t_block);
    ft_putstr(BH);
    while (i < size)
    {
        chr = *(char *)((void *)blk + i);
        if (blk->freed)
            ft_putstr(FREED);
        else if ((int)chr > 31 && (int)chr < 127)
            ft_putchar(chr);
        else
            ft_putstr(FILL);
        i++;
    }
    return size;
}

/*
 *
 *  print page user 
 * 
 * g->|PH▒▒▒.......Hxxxxx....Hxxx...Hxx..|
 * page: 0x...
 * prev: 0x...
 * next: 0x...
 * type: 
 * total_size:
 * free_size:
 * block_count:
 *
 */

void    prefix_putnbr_base(char *str, size_t nbr, int base)
{
    ft_putstr(str);
    ft_itoa_base(nbr, base);
	ft_putstr("\n");
}

void    print_block_header(t_block *blk)
{
    prefix_putnbr_base("block: 0x", (size_t)blk, 16);
    prefix_putnbr_base("prev: 0x", (size_t)blk->prev, 16);
    prefix_putnbr_base("next: 0x", (size_t)blk->next, 16);
    prefix_putnbr_base("freed: ", (size_t)blk->freed, 10);
    prefix_putnbr_base("size: ", (size_t)blk->size, 10);
    prefix_putnbr_base("size of header(t_block): ",
            (size_t)sizeof(t_block), 10);
}

void    print_page_header(t_page *page)
{
    prefix_putnbr_base("prev: 0x", (size_t)page->prev, 16);
    prefix_putnbr_base("next: 0x", (size_t)page->next, 16);
    ft_putstr("type: ");
    if (page->type == TINY)
       ft_putstr("TINY");
    else if (page->type == SMALL)
       ft_putstr("SMALL");
    else
       ft_putstr("LARGE");
	ft_putstr("\n");
    prefix_putnbr_base("total_size: ", (size_t)page->total_size, 10);
    prefix_putnbr_base("free_size: ", (size_t)page->free_size, 10);
    prefix_putnbr_base("block_count: ", (size_t)page->block_count, 10);
    prefix_putnbr_base("size of header(t_page): ",
            (size_t)sizeof(t_page), 10);
}

void    print_all_page_headers(void)
{
    t_page *g_page;
    int     i;

    i = 0;
    g_page = g_malloc_page;
    ft_putstr("---all page---\n");
    while (g_page)
    {
        prefix_putnbr_base("Page number: ", i, 10);
        print_page_header(g_page);
        g_page = g_page->next;
        i++;
    }
    ft_putstr("---all page---\n");
}

void    print_graph_page(t_page *page)
{
    t_block     *blk;
    size_t      i = 0;

    if (!page)
        return ;
    ft_putstr("G->|");
    ft_putstr(PH);
    blk = PAGE_SHIFT(page);
    i = sizeof(t_page);
    while (i < page->total_size)
    {
        if (((void *)page + i) == (void *)blk)
        {
            i += print_graph_blk(blk);
            blk = blk->next;
        }
        else
        {
           ft_putstr(".");
           i++;
        }
    }
    ft_putstr("|\n");
    print_page_header(page);
}
