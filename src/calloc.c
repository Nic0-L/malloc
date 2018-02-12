/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** calloc
*/

#include "malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	size = ALIGN_SIZE(nmemb * size);
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}
