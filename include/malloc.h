/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>

typedef struct block_s	block_t;

struct	block_s
{
	size_t		size;
	block_t		*prev;
	block_t		*next;
	block_t		*prev_free;
	block_t		*next_free;
	char		free;
};

#define HEADER_SIZE	sizeof(block_t)

#if     UINTPTR_MAX == 0xFFFFFFFF
# define	ALIGN_SIZE(x)	((((x) + 3) >> 2) << 2)
#elif	UINTPTR_MAX == 0xFFFFFFFFFFFFFFFF
# define	ALIGN_SIZE(x)	((((x) + 7) >> 3) << 3)
#endif

#define BLOCK_DATA(x)	((void *)(x) + (size_t)HEADER_SIZE)
#define DATA_BLOCK(x)	((block_t*)((void *)(x) - (size_t)HEADER_SIZE))

extern pthread_mutex_t	malloc_mutex;
extern block_t		*first_block;
extern block_t		*last_block;
extern block_t		*first_free;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void	show_alloc_mem(void);
void	malloc_split(block_t *block, size_t size);
void	free_list_add(block_t *block);
void	free_list_remove(block_t *block);
block_t	*free_list_get(size_t size);
int	realloc_extend(block_t *block, size_t size);
void	*malloc_no_lock(size_t size);
void	free_no_lock(void *ptr);
block_t	*malloc_move_brk(size_t size);

#endif
