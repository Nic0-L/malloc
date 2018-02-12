/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** free_list
*/

#include "malloc.h"

void		free_list_place(block_t *block)
{
	register block_t	*pos = first_free;

	while (pos) {
		if (pos->next_free == NULL			\
		|| pos->next_free->size >= block->size) {
			block->prev_free = pos;
			block->next_free = pos->next_free;
			pos->next_free = block;
			if (block->next_free != NULL)
				block->next_free->prev_free = block;
			return;
		}
		pos = pos->next_free;
	}
}

void		free_list_add(block_t *block)
{
	if (first_free == NULL) {
		block->prev_free = NULL;
		block->next_free = NULL;
		first_free = block;
		return;
	}
	if (first_free->size >= block->size) {
		block->prev_free = NULL;
		block->next_free = first_free;
		first_free->prev_free = block;
		first_free = block;
		return;
	}
	free_list_place(block);
}

void    free_list_remove(block_t *block)
{
	if (block->prev_free != NULL)
		block->prev_free->next_free = block->next_free;
	else
		first_free = block->next_free;
	if (block->next_free != NULL)
		block->next_free->prev_free = block->prev_free;
}

block_t	*free_list_get(size_t size)
{
	register block_t	*block = first_free;

	while (block) {
		if (block->size >= size) {
			block->free = 0;
			free_list_remove(block);
			malloc_split(block, size);
			return (block);
		}
		block = block->next_free;
	}
	return (NULL);
}
