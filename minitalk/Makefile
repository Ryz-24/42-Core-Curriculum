CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME_CLIENT = client
NAME_SERVER = server

PRINTF_DIR = ft_printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

SRC_CLIENT = client.c
SRC_SERVER = server.c

all: $(PRINTF_LIB) $(NAME_CLIENT) $(NAME_SERVER)

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

$(NAME_CLIENT): $(SRC_CLIENT) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(SRC_CLIENT) $(PRINTF_LIB) -o $(NAME_CLIENT)

$(NAME_SERVER): $(SRC_SERVER) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(PRINTF_LIB) -o $(NAME_SERVER)

clean:
	make -C $(PRINTF_DIR) clean

fclean: clean
	make -C $(PRINTF_DIR) fclean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re
