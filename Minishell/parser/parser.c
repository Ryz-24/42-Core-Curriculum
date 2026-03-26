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

static const char *redir_type_str(t_token_type type)
{
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

static void print_redirections(t_redir *redir)
{
    if (!redir)
        return;
    printf("redirections:\n");
    while (redir)
    {
        printf("  type: %s\n", redir_type_str(redir->type));
        printf("  file: %s\n", redir->file);
        redir = redir->next;
    }
}
/* print_commands:
**	Debug function that prints the content of the command list,
**	including argv and associated redirections.
**
**	This is used during development to verify that parsing
**	was done correctly.
**
**	IMPORTANT:
**	This function must not be used in the final version of
**	minishell, as it produces extra output not present in bash.
*/
void print_commands(t_cmd *cmds)
{
    int i;
    int j;

    i = 1;
    while (cmds)
    {
        printf("CMD %d\n", i);
        j = 0;
        if (cmds->argv)
        {
            while (cmds->argv[j])
            {
                printf("argv[%d]: %s\n", j, cmds->argv[j]);
                j++;
            }
        }
        print_redirections(cmds->redir);
        printf("\n");
        cmds = cmds->next;
        i++;
    }
}