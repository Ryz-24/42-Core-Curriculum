# NAME = so_long

# CC = cc
# CFLAGS = -Wall -Wextra -Werror

# LIBFT = libft/libft.a
# MLX = -lmlx -lXext -lX11

# SRC = main.c \
#       map_read.c \
#       map_check.c \
#       map_path.c \
#       movements.c \
#       rendering.c \
# 	  get_next_line/get_next_line.c \
# 	  get_next_line/get_next_line_utils.c

# OBJ = $(SRC:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJ)
# 	make -C libft
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

# clean:
# 	make -C libft clean
# 	rm -f $(OBJ)

# fclean: clean
# 	make -C libft fclean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re


NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC = main.c \
      map_read.c \
      map_check.c \
      map_path.c \
      movements.c \
      rendering.c \
      get_next_line/get_next_line.c \
      get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
