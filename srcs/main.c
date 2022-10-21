/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:00:52 by zweng             #+#    #+#             */
/*   Updated: 2022/10/21 15:58:12 by vagrant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void    input_value(int *src, size_t size)
{
    size_t i = 0;
    while (i < size)
    {
       src[i] = i; 
       i++;
    }
}

int     main()
{
    char *ptr = NULL;
    int     *ptr1 = NULL;
    int     *ptr2 = NULL;
    if ((ptr = ft_malloc(11)))
    {
        ft_strcpy(ptr, "1234567890");
        printf("result %s\n", ptr);
    }
    if ((ptr1 = ft_malloc(sizeof(int) * 50)))
    {
        input_value(ptr1, 50);
        printf("result %d\n", ptr1[45]);
    }
    if ((ptr2 = ft_malloc(sizeof(int) * 915000)))
    {
        input_value(ptr2, 915000);
        printf("result %d\n", ptr2[100110]);
    }
    printf("g_malloc_page: %p\n", (void *)g_malloc_page);
    show_alloc_mem();
    ft_free(ptr);
    return 0;
}
