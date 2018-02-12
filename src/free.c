/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** free
*/

#include "malloc.h"

void		free_move_brk(block_t *block)
{
	size_t	size;

	if (block->prev == NULL) {
		first_block = NULL;
		last_block = NULL;
		brk((void *)block);
		return;
	}
	size = (HEADER_SIZE + block->size) % getpagesize();
	if (size <= HEADER_SIZE) {
		last_block = block->prev;
		block->prev->size += size;
		block->prev->next = NULL;
		brk((void *)block->prev + HEADER_SIZE + block->prev->size);
		return;
	}
	block->size -= (block->size / getpagesize()) * getpagesize();
	brk(block + HEADER_SIZE + block->size);
	free_list_add(block);
}

void		free_fusion_next(block_t *block)
{
	block->size += HEADER_SIZE + block->next->size;
	block->next = block->next->next;
	if (block->next != NULL)
		block->next->prev = block;
	else
		last_block = block;
}

void		free_fusion(block_t *block)
{
	register block_t *tmp = block->prev;

	if (tmp != NULL && tmp->free == 1) {
		block = tmp;
		free_list_remove(block);
		free_fusion_next(block);
	}
	tmp = block->next;
	if (tmp != NULL && tmp->free == 1) {
		free_list_remove(tmp);
		free_fusion_next(block);
	}
	if (tmp == NULL && HEADER_SIZE + block->size >= (size_t)getpagesize())
		free_move_brk(block);
	else
		free_list_add(block);
}

void	free_no_lock(void *ptr)
{
	block_t	*block = DATA_BLOCK(ptr);

	if (ptr == NULL || block->free == 1)
		return;
	block->free = 1;
	free_fusion(block);
}

void	free(void *ptr)
{
	block_t	*block = DATA_BLOCK(ptr);

	if (ptr == NULL || block->free == 1)
		return;
	pthread_mutex_lock(&malloc_mutex);
	block->free = 1;
	free_fusion(block);
	pthread_mutex_unlock(&malloc_mutex);
}
