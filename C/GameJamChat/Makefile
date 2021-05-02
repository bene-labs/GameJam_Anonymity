##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## ftp
##

SRC	=	main.c					\
		server/server.c			\
		server/connect.c		\
		server/basic_commands.c	\
		user_info.c				\
		user_info2.c			\
		server/file_commands.c

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS += 	-Wextra #-Werror

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		clean fclean all re
