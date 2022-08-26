/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:46 by zweng             #+#    #+#             */
/*   Updated: 2022/08/25 14:15:49 by vagrant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include "libft.h"


/*
** For a pagesize of 4096 bytes
**
** TINY  - block < 128 bytes  - heap 16 KB
** SMALL - block < 1024 bytes - heap 128 KB
** LARGE - block > 1024 bytes
*/

# define PAGE_SHIFT(start) ((void *)start + sizeof(t_page))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

# define PAYLOAD_SIZE(total_s, header_s) (total_s - header_s)

/* tiny page = 4 * 4096  = 16384 bytes */
# define TINY_ZONE (4 * getpagesize())
/* tiny block = 16384 / 128 (times of allocation) = 128 bytes 
 * a tiny block 128 bytes 
 * */
# define TINY_BLOCK (TINY_ZONE / 128)
/* tiny page = 32 * 4096  = 131072 bytes */
# define SMALL_ZONE (32 * getpagesize())
/* tiny block = 131072/ 128 (times of allocation) = 1024 bytes 
 * a tiny block 128 bytes 
 * */
# define SMALL_BLOCK (SMALL_ZONE / 128)

typedef	enum
{
	MALLOC_TINY,
	MALLOC_SMALL,
	MALLOC_LARGE
}	t_malloc_type;

typedef enum	e_page_type {
	TINY,
	SMALL,
	LARGE
}				t_page_type;

// 10 byte
typedef struct			s_block
{
    int                 freed;
    size_t              size;
	struct s_block		*next;
	struct s_block		*prev;
}						t_block;

// 8 byte
typedef struct	s_page {
	struct s_page	*prev;
	struct s_page	*next;
	t_page_type     type;
	struct s_block	*allocated;
	struct s_block	*freed;
	size_t			total_size;
	size_t			free_size;
	size_t			block_count;
}				t_page;

extern pthread_mutex_t	g_malloc_mutex;
extern t_page		    *g_malloc_page;

/*
** Library methods
*/

void			*ft_malloc(size_t size);
void			*calloc(size_t count, size_t size);
void			*realloc(void *ptr, size_t size);
void			*reallocf(void *ptr, size_t size);
void			free(void *ptr);
void			show_alloc_mem();
void			show_alloc_mem_hex(void);


/*
 * util functions
 */
void            insert_block(t_block *blk, t_block *blk_insert);
void            set_block(t_block *blk, size_t size);
t_block         *set_block_safe(t_block *blk, size_t size, size_t old_size);
t_page_type     get_page_type(size_t size);
t_block         *find_available_block(size_t size, t_page **page);
t_block         *try_create_new_block(size_t size);
size_t          get_page_size_from_block_type(t_page_type type, size_t size);
t_block         *try_find_available_block(size_t size);

#endif