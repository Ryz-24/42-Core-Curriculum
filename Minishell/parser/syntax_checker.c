#include "minishell.h"

/* check_syntax:
**	Validates the token list to ensure the input command follows
**	valid shell syntax rules before parsing.
**
**	Checks include:
**	- No leading pipe
**	- No consecutive pipes (||)
**	- Redirections must be followed by a WORD (filename)
**	- No redirection at end of input
**
**	If an error is detected, an appropriate error message is
**	printed to stderr and parsing is stopped.
**
**	Returns:
**	- 0 if syntax is valid
**	- 1 if a syntax error is found
*/
int check_syntax(t_token *tokens)
{
    t_token *curr;

    if (!tokens)
        return (0);

    if (tokens->type == PIPE)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (1);
    }

    curr = tokens;
    while (curr)
    {
        if (curr->type == PIPE)
        {
            if (!curr->next || curr->next->type == PIPE)
            {
                printf("minishell: syntax error near unexpected token `|'\n");
                return (1);
            }
        }

        if (is_redirection(curr->type))
        {
            if (!curr->next)
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return (1);
            }

            if (curr->next->type != WORD)
            {
                printf("minishell: syntax error near unexpected token `%s'\n",
                       curr->next->value);
                return (1);
            }
        }

        curr = curr->next;
    }

    return (0);
}