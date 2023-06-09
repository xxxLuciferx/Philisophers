NAME = philo
# NAME_BONUS = checker

SRC = Philosophers.c Parsing.c
# SRC_BONUS = bonus_checker.c ft_split.c ft_strjoin.c ft_atoi.c ft_lst.c \
# 			swaps.c swaps2.c magic.c algorithmes.c list_to_stack.c bonus_files1.c bonus_files2.c bonus_files3.c  \
# 			get_next_line.c get_next_line_utils.c


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