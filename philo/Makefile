NAME = philo

SRC = Philosophers.c Parsing.c routine.c tools.c

CFLAGS = -Wall -Wextra -Werror 

OBJ = ${SRC:.c=.o}

all : $(NAME)


$(NAME): $(OBJ)
		cc $(CFLAGS) $^ -o$(NAME)


clean : 
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all