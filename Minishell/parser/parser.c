#include "minishell.h"

/* parse_tokens:
**	Converts a flat list of tokens into a structured linked list
**	of commands (t_cmd).
**
**	This is the core of the parsing stage, where tokens are grouped
**	into commands, arguments, pipes, and redirections.
**
**	Behavior:
**	- WORD tokens are added to the current command's argv
**	- Redirection tokens create a t_redir node and are attached
**	  to the current command
**	- PIPE tokens create a new command node and link it to the
**	  current one
**
**	The result is a linked list where each node represents a
**	command ready for execution.
**
**	On any error (allocation failure or invalid structure),
**	the function frees all allocated memory and returns NULL.
**
**	Returns:
**	- Head of the t_cmd list on success
**	- NULL on failure
*/
t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd   *head;
    t_cmd   *curr;
    t_redir *redir;

    if (!tokens)
        return (NULL);

    head = cmd_new();
    if (!head)
        return (NULL);
    curr = head;

    while (tokens)
    {
        if (tokens->type == WORD)
        {
            if (cmd_add_arg(curr, tokens->value, tokens->quote))
            {
                cmd_clear(&head);
                return (NULL);
            }
        }
        else if (is_redirection(tokens->type))
        {
            t_token_type type = tokens->type;

            tokens = tokens->next;
            if (!tokens || tokens->type != WORD)
            {
                cmd_clear(&head);
                return (NULL);
            }

            redir = redir_new(type, tokens->value);
            if (!redir)
            {
                cmd_clear(&head);
                return (NULL);
            }

            redir_add_back(&curr->redir, redir);
        }
        else if (tokens->type == PIPE)
        {
            curr->pipe_to_next = 1;
            curr->next = cmd_new();
            if (!curr->next)
            {
                cmd_clear(&head);
                return (NULL);
            }
            curr = curr->next;
        }
        tokens = tokens->next;
    }
    return (head);
}
