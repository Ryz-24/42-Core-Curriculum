#include "minishell.h"

/* token_create:
**	Allocates and initializes a new token (t_token).
**
**	The token stores:
**	- Type (WORD, PIPE, REDIR, etc.)
**	- Value (string)
**	- Quote type
**
**	The value is duplicated to ensure safe memory ownership.
**
**	Returns:
**	- Pointer to new token
**	- NULL on allocation failure
*/
t_token *token_create(t_token_type type, char *value, t_quote_type quote)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->quote = quote;
    if (value)
    {
        token->value = strdup(value);
        if (!token->value)
        {
            free(token);
            return (NULL);
        }
    }
    else
        token->value = NULL;
    token->next = NULL;
    return (token);
}

void token_add_back(t_token **list, t_token *tokn)
{
    t_token *tmp;

    if (!list || !tokn)
        return;
    if (*list == NULL)
    {
        *list = tokn;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = tokn;
}

/* token_clear:
**	Frees an entire linked list of tokens, including:
**	- The value string of each token
**	- The token nodes themselves
**
**	Used for cleanup in case of errors during lexing or parsing.
*/
void token_clear(t_token **list)
{
    t_token *tmp;

    if (!list || !*list)
        return;
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->value);
        free(*list);
        *list = tmp;
    }
}