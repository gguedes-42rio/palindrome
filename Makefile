NAME	=	palindrome

SRC		=	palindrome.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra -I.

CC		=	cc

RM		=	rm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONE: all clean fclean re
