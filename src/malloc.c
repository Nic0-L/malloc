/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc
*/

#include "malloc.h"

pthread_mutex_t	malloc_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
block_t		*first_block = NULL;
block_t		*last_block = NULL;
block_t		*first_free = NULL;

void		malloc_split(block_t *block, size_t size)
{
	block_t	*new_block;

	if (block->size - size <= HEADER_SIZE)
		return;
	new_block = (void *)block + HEADER_SIZE + size;
	new_block->size = block->size - size - HEADER_SIZE;
	new_block->prev = block;
	new_block->next = block->next;
	new_block->free = 1;
	free_list_add(new_block);
	block->size = size;
	block->next = new_block;
	if (new_block->next != NULL)
		new_block->next->prev = new_block;
	else
		last_block = new_block;
}

void		*malloc_no_lock(size_t size)
{
	block_t	*block;

	if (size == 0)
		return (NULL);
	size = ALIGN_SIZE(size);
	block = free_list_get(size);
	if (block != NULL)
		return (BLOCK_DATA(block));
	block = malloc_move_brk(size);
	if (block == NULL)
		return (NULL);
	if (first_block == NULL)
		first_block = block;
	return (BLOCK_DATA(block));
}

void		*malloc(size_t size)
{
	block_t	*block;

	if (size == 0)
		return (NULL);
	size = ALIGN_SIZE(size);
	pthread_mutex_lock(&malloc_mutex);
	block = free_list_get(size);
	if (block != NULL) {
		pthread_mutex_unlock(&malloc_mutex);
		return (BLOCK_DATA(block));
	}
	block = malloc_move_brk(size);
	if (block == NULL) {
		pthread_mutex_unlock(&malloc_mutex);
		return (NULL);
	}
	if (first_block == NULL)
		first_block = block;
	pthread_mutex_unlock(&malloc_mutex);
	return (BLOCK_DATA(block));
}
