/*
CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

LIBFT_PATH = libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a

CLIENT_NAME = client
SERVER_NAME = server

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -L$(LIBFT_PATH) -lft

$(SERVER_NAME): $(SERVER_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_SRCS) -L$(LIBFT_PATH) -lft

clean:
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
*/


CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client
PRINTF = ft_printf.c

all: $(SERVER) $(CLIENT)

$(SERVER): server.c $(PRINTF)
	$(CC) $(CFLAGS) server.c $(PRINTF) -o $(SERVER)

$(CLIENT): client.c $(PRINTF)
	$(CC) $(CFLAGS) client.c $(PRINTF) -o $(CLIENT)

clean:
	rm -f *.o

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all
