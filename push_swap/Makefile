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

NAME    = push_swap

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = chunks_sort.c error_check.c handle_pos.c index.c \
          op_push.c op_reverse_rotate.c op_rotate.c op_swap.c \
          parse_args.c push_swap.c sort_small.c stack_init.c \
          stack_utils.c utils.c

OBJS    = $(SRCS:.c=.o)

LIBFT   = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
