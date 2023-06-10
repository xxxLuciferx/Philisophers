NAME = philo

SRC = Philosophers.c Parsing.c routine.c


####### ADD FLAGS
CFLAGS = -Wall -Wextra -Werror -pthread
# CFLAGS = -fsanitize=address -g

OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

all : $(NAME)


$(NAME): $(OBJ)
		cc $(CFLAGS) $^ -o$(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
		cc $(CFLAGS) $^ -o $(NAME_BONUS)

clean : 
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all