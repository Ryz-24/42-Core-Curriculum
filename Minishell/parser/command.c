#include "minishell.h"

/* cmd_new:
**	Allocates and initializes a new command structure (t_cmd).
**	This represents a single command in the pipeline.
**
**	All fields are initialized to NULL (or 0) so the parser
**	can safely build the structure step by step.
**
**	Returns:
**	- Pointer to newly allocated t_cmd
**	- NULL if allocation fails
*/
t_cmd *cmd_new(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->quotes = NULL;
    cmd->redir = NULL;
    cmd->pipe_to_next = 0;
    cmd->next = NULL;
    return (cmd);
}

/* cmd_add_arg:
**	Adds a new argument to a command's argv array, while also
**	tracking the quote type for that argument.
**
**	Since argv is a NULL-terminated dynamic array, a new array
**	is allocated with size +1, old values are copied, and the
**	new argument is appended at the end.
**
**	A parallel array (quotes) is maintained to store whether
**	each argument was quoted (single, double, or none), which
**	is later used during expansion.
**
**	Old arrays are freed after copying to avoid memory leaks.
**
**	Returns:
**	- 0 on success
**	- 1 on allocation failure
*/
int cmd_add_arg(t_cmd *cmd, char *arg, t_quote_type quote)
{
    int len;
    int i;
    char **new_argv;
    t_quote_type *new_quotes;

    len = argv_len(cmd->argv);

    new_argv = malloc(sizeof(char *) * (len + 2));
    new_quotes = malloc(sizeof(t_quote_type) * (len + 1));
    if (!new_argv || !new_quotes)
    {
        free(new_argv);
        free(new_quotes);
        return (1);
    }

    i = 0;
    while (i < len)
    {
        new_argv[i] = cmd->argv[i];
        new_quotes[i] = cmd->quotes[i];
        i++;
    }

    new_argv[i] = strdup(arg);
    if (!new_argv[i])
    {
        free(new_argv);
        free(new_quotes);
        return (1);
    }
    new_quotes[i] = quote;

    new_argv[i + 1] = NULL;

    free(cmd->argv);
    free(cmd->quotes);

    cmd->argv = new_argv;
    cmd->quotes = new_quotes;

    return (0);
}