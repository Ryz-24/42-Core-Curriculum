#include "minishell.h"

const char *token_type_str(t_token_type type)
{
    if (type == WORD)
        return ("WORD");
    if (type == PIPE)
        return ("PIPE");
    if (type == REDIR_IN)
        return ("REDIR_IN");
    if (type == REDIR_OUT)
        return ("REDIR_OUT");
    if (type == REDIR_APPEND)
        return ("REDIR_APPEND");
    if (type == HEREDOC)
        return ("HEREDOC");
    return ("UNKNOWN");
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("%s", token_type_str(tokens->type));
        if (tokens->value)
            printf(": %s", tokens->value);
        printf("\n");
        tokens = tokens->next;
    }
}