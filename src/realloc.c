/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** realloc
*/

#include "malloc.h"

void		*realloc_malloc(void *ptr, size_t size, size_t old_size)
{
	void	*new_ptr;

	new_ptr = malloc_no_lock(size);
	if (new_ptr == NULL)
		return (NULL);
	memcpy(new_ptr, ptr, old_size);
	free_no_lock(ptr);
	return (new_ptr);
}

void		*realloc(void *ptr, size_t size)
{
	int	extended;
	block_t	*block = DATA_BLOCK(ptr);

	if (ptr == NULL || size == 0)
		return (malloc(size));
	size = ALIGN_SIZE(size);
	pthread_mutex_lock(&malloc_mutex);
	extended = realloc_extend(block, size);
	if (extended) {
		pthread_mutex_unlock(&malloc_mutex);
		return (ptr);
	}
	ptr = realloc_malloc(ptr, size, block->size);
	pthread_mutex_unlock(&malloc_mutex);
	return (ptr);
}
