NAME = philo
FILES = philo_main.c before_simulatoin.c extra_functoins.c
OBJ_FILES = $(FILES:.c=.o)
C_flags =  -Wall -Wextra -Werror 

$(NAME): $(OBJ_FILES)
	cc $(C_flags) $(OBJ_FILES) -o $(NAME)

all:$(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all