NAME	=	palindrome

SRC		=	palindrome.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra -I.

CC		=	cc

RM		=	rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONE: all clean fclean re
