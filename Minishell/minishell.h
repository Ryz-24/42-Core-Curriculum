#ifndef MINISHELL_H
#define MINISHELL_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

extern int g_exit_status; //the exit status of the LAST executed command

typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC
} t_token_type;

typedef enum e_quote_type
{
    NO_QUOTE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE
} t_quote_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    t_quote_type    quote;
    struct s_token  *next;
} t_token;

typedef struct s_redir
{
    t_token_type    type;
    char            *file;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **argv;
    t_quote_type    *quotes;
    t_redir         *redir;
    int             pipe_to_next;
    struct s_cmd    *next;
}   t_cmd;

// lexer
t_token *lexer(char *input);
char    *read_word(char *input, int *i, t_quote_type *quote);
char    *read_quoted(char *input, int *i, t_quote_type *quote);
t_token *create_operator_token(char *input, int *i);

// lexer utils
int     is_space(char c);
int     is_operator(char c);
char    *strjoin_free(char *s1, char *s2);
int     operator_length(char *s);
t_token_type operator_type(char *s);

// tokens
t_token *token_create(t_token_type type, char *value, t_quote_type quote);
void    token_add_back(t_token **list, t_token *tokn);
void    token_clear(t_token **list);

// parser
t_cmd   *parse_tokens(t_token *tokens);
t_cmd   *cmd_new(void);
int     cmd_add_arg(t_cmd *cmd, char *arg, t_quote_type quote);
void    cmd_clear(t_cmd **cmds);
int     argv_len(char **argv);

// syntax
int     check_syntax(t_token *tokens);

// redirection
t_redir *redir_new(t_token_type type, char *file);
void    redir_add_back(t_redir **list, t_redir *new);
void    redir_clear(t_redir *redir);
int     is_redirection(t_token_type type);

// expander
int     expand_commands(t_cmd *cmds, char **envp);
char    *expand_string(char *str, char **envp);
int     is_var_char(char c);

// env
char    *get_env_value(char *name, char **envp);

// debug
void    print_tokens(t_token *tokens);
void    print_commands(t_cmd *cmds);

// quote checker
int     check_quotes(char *input);

#endif