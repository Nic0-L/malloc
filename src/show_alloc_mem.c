/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** show_alloc_mem
*/

#include "malloc.h"

void	show_alloc_str(char *str)
{
	write(1, str, strlen(str));
}

void	show_alloc_nbr(size_t nb, char *base)
{
	size_t	size = strlen(base);
	char	c;

	if (nb >= size)
		show_alloc_nbr(nb / size, base);
	c = base[nb % size];
	write(1, &c, 1);
}

void	show_alloc_mem(void)
{
	block_t	*block = first_block;
	size_t	size;

	show_alloc_str("break : 0x");
	show_alloc_nbr((size_t)sbrk(0), "0123456789ABCDEF");
	show_alloc_str("\n");
	while (block) {
		size = block->size;
		show_alloc_str("0x");
		show_alloc_nbr((size_t)BLOCK_DATA(block), "0123456789ABCDEF");
		show_alloc_str(" - 0x");
		show_alloc_nbr((size_t)BLOCK_DATA(block) + size,	\
				"0123456789ABCDEF");
		show_alloc_str(" : ");
		show_alloc_nbr(size, "0123456789");
		show_alloc_str(" free: ");
		show_alloc_nbr((size_t)block->free, "0123456789");
		show_alloc_str("\n");
		block = block->next;
	}
}
