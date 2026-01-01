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

NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = 	chunks_sort.c\
	error_check.c\
	handle_pos.c\
	index.c\
	op_push.c\
	op_swap.c\
	op_rotate.c\
	op_reverse_rotate.c\
	parse_args.c\
	push_swap.c\
	sort_small.c\
	stack_func.c\
	utils.c\
	libft/libft.a

$(NAME) :
	make -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(NAME)
	make clean -C libft

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

re : fclean all


