##
## EPITECH PROJECT, 2018
## malloc
## File description:
## malloc
##

NAME	=	libmy_malloc.so

SRCS	=	src/malloc.c		\
		src/malloc_move_brk.c	\
		src/realloc.c		\
		src/realloc_extend.c	\
		src/calloc.c		\
		src/free.c		\
		src/show_alloc_mem.c	\
		src/free_list.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS 	=	-W -Wall -Wextra -I include -fpic

CC	=	gcc

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -shared -o $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

mrclean:
		find -name "*~" -delete -o -name "#*#" -delete

fclean:		clean
		rm -f $(NAME)

re:		fclean all

cleanall:	fclean mrclean
