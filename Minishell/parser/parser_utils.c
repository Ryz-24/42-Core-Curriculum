#include "minishell.h"

int  argv_len(char **argv)
{
    int i;

    if (!argv)
        return (0);
    i = 0;
    while (argv[i])
        i++;
    return (i);
}

/*if (is_redir_only(cmd))
{
    // Apply redirections only
    // DO NOT call execve
    return ;
}*/
/* is_redir_only:
**	Checks whether a command contains only redirections and
**	no actual executable arguments.
**
**	This is useful during execution to handle cases like:
**		> file.txt
**	where no command is present, but redirections must still
**	be applied.
**
**	Returns:
**	- 1 if command has no argv but has redirections
**	- 0 otherwise
*/
int is_redir_only(t_cmd *cmd)
{
    return (!cmd->argv && cmd->redir);
}

/* cmd_clear:
**	Frees an entire linked list of commands (t_cmd), including:
**	- argv array and each string inside it
**	- quotes array
**	- redirection list (via redir_clear)
**
**	This function is used for cleanup in case of errors during
**	parsing or execution, ensuring no memory leaks occur.
**
**	The pointer is updated progressively to safely traverse and
**	free the entire list.
*/
void cmd_clear(t_cmd **cmds)
{
    t_cmd   *tmp;
    int     i;

    while (*cmds)
    {
        tmp = (*cmds)->next;

        if ((*cmds)->argv)
        {
            i = 0;
            while ((*cmds)->argv[i])
            {
                free((*cmds)->argv[i]);
                i++;
            }
            free((*cmds)->argv);
        }

        redir_clear((*cmds)->redir);
        free((*cmds)->quotes);
        free(*cmds);
        *cmds = tmp;
    }
}

