# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/01 14:13:45 by rzaatreh          #+#    #+#              #
#    Updated: 2026/01/01 14:15:36 by rzaatreh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

RM          = rm -f

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = fun1.c fun2.c fun3.c fun4.c fun5.c \
              fun6.c fun7.c fun8.c fun9.c \
              fun10.c fun11.c fun12.c fun13.c

OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I. -I$(LIBFT_DIR)

# ================= RULES ================= #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
