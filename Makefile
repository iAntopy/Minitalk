
SRC_DIR		= src/

SRC_SRV		= server.c 
SRC_CLT		= client.c 

OBJ_SRV		= server.o
OBJ_CLT		= client.o

LIBFT		= ../libft/libft.a

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME_SRV	= server
NAME_CLT	= client

%.o:		%.c
		-$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME_SRV) $(NAME_CLT)

$(NAME_SRV):	$(LIBFT) $(OBJ_SRV)
		$(CC) $(CFLAGS) -o $(NAME_SRV) $(OBJ_SRV) $(LIBFT)

$(NAME_CLT):	$(LIBFT) $(OBJ_CLT)
		$(CC) $(CFLAGS) -o $(NAME_CLT) $(OBJ_CLT) $(LIBFT)

$(LIBFT):
		make -C ../libft/

#bonus:		$(NAME_BONUS)

clean:
		rm -f $(OBJ_SRV) $(OBJ_CLT) $(LIBFT)

fclean:		clean
		rm -f $(NAME_SRV) $(NAME_CLT)

re:			fclean all
