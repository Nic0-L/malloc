/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** realloc_extend
*/

#include "malloc.h"

void		realloc_move_brk(block_t *block, size_t size)
{
	size_t	page_size = getpagesize();
	size_t	total = (((size - block->size) / page_size) + 1) * page_size;

	if (sbrk(total) == (void *)-1)
		return;
	block->size += total;
	malloc_split(block, size);
}

void		realloc_use_next_free(block_t *block, size_t size)
{
	free_list_remove(block->next);
	block->size += HEADER_SIZE + block->next->size;
	block->next = block->next->next;
	if (block->next != NULL)
		block->next->prev = block;
	else
		last_block = block;
	malloc_split(block, size);
}

void		realloc_reduce_size(block_t *block, size_t size)
{
	if (block->size == size)
		return;
	if (block->next != NULL && block->next->free == 1)
		realloc_use_next_free(block, block->size + HEADER_SIZE	\
					+ block->next->size);
	malloc_split(block, size);
}

int		realloc_extend(block_t *block, size_t size)
{
	if (block->size >= size) {
		realloc_reduce_size(block, size);
		return (1);
	}
	if (block->next == NULL) {
		realloc_move_brk(block, size);
		return (1);
	}
	if (block->next->free == 1 \
	&& block->size + HEADER_SIZE + block->next->size >= size) {
		realloc_use_next_free(block, size);
		return (1);
	}
	return (0);
}
