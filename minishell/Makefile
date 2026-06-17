NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I.

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

READLINE	= -lreadline

SRC			= main.c \
			  shell_init.c \
			  lexer/lexer.c \
			  lexer/lexer_utils.c \
			  lexer/token.c \
			  lexer/quote_check.c \
			  parser/parser.c \
			  parser/parser_utils.c \
			  parser/command.c \
			  parser/redirection.c \
			  parser/syntax_checker.c \
			  expander/expand.c \
			  expander/expand_var.c \
			  expander/expand_utils.c \
			  executor/executor.c \
			  executor/executor_core.c \
			  executor/executor_redir.c \
			  executor/executor_utils.c \
			  executor/executor_sig.c \
			  executor/executor_path.c \
			  executor/heredoc.c \
			  executor/heredoc_utils.c \
			  builtins/builtin_cd.c \
			  builtins/builtin_echo.c \
			  builtins/builtin_env.c \
			  builtins/builtin_exit.c \
			  builtins/builtin_export.c \
			  builtins/builtin_pwd.c \
			  builtins/builtin_unset.c \
			  builtins/builtin_utils.c

OBJ			= $(SRC:.c=.o)

RM			= rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
