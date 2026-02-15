NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread

SRC			= main.c \
			  main_helper.c \
			  init.c \
			  time.c \
			  forks.c \
			  action.c \
			  monitor.c \
			  utils.c \
			  routine.c

OBJ			= $(SRC:.c=.o)

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
