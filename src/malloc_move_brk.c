/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc_move_brk
*/

#include "malloc.h"

block_t		*malloc_move_brk_last_used(size_t size)
{
	block_t	*new;
	size_t	total;

	total = (((size + HEADER_SIZE) / getpagesize()) + 1) * getpagesize();
	new = sbrk(total);
	if ((void *)new == (void *)-1)
		return (NULL);
	new->size = total - HEADER_SIZE;
	new->prev = last_block;
	new->next = NULL;
	new->free = 0;
	if (new->prev != NULL)
		new->prev->next = new;
	last_block = new;
	malloc_split(new, size);
	return (new);
}

block_t		*malloc_move_brk_last_free(size_t size)
{
	size_t	total;
	block_t	*block = last_block;

	free_list_remove(block);
	block->free = 0;
	total = (((size - block->size) / getpagesize()) + 1) * getpagesize();
	if (sbrk(total) == (void *)-1)
		return (NULL);
	block->size += total;
	malloc_split(block, size);
	return (block);
}

block_t		*malloc_move_brk(size_t size)
{
	if (last_block == NULL || last_block->free == 0)
		return (malloc_move_brk_last_used(size));
	return (malloc_move_brk_last_free(size));
}
