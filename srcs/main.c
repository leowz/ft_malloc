/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:35:46 by zweng             #+#    #+#             */
/*   Updated: 2022/11/01 22:00:42 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

#define M (10 * 1)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
    int i;
	char *addr;

	i = 0;
	while (i < 1025)
	{
		addr = (char*)ft_malloc(1023);
		strcpy(addr, "123456789\n");
        ft_free(addr);
		i++;
	}
	show_alloc_mem();
    print_graph_page(g_malloc_page);
    print_all_page_headers();
	return (0);
}

