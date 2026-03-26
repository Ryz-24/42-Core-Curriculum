#include "minishell.h"

int is_redirection(t_token_type type)
{
    return (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND || type == HEREDOC);
}
/* redir_new:
**	Creates and initializes a new redirection node (t_redir).
**
**	The node stores:
**	- The type of redirection (>, >>, <, <<)
**	- The associated file name (duplicated string)
**
**	This structure is later used during execution to apply
**	file descriptor redirections.
**
**	Returns:
**	- Pointer to new redirection node
**	- NULL on allocation failure
*/
t_redir *redir_new(t_token_type type, char *file)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->file = strdup(file);
    if (!redir->file)
    {
        free(redir);
        return (NULL);
    }
    redir->next = NULL;
    return (redir);
}
/* redir_add_back:
**	Appends a redirection node to the end of a command's
**	redirection list.
**
**	If the list is empty, the new node becomes the head.
**	Otherwise, the function traverses the list and attaches
**	the new node at the end.
*/
void redir_add_back(t_redir **list, t_redir *new)
{
    t_redir *tmp;

    if (!*list)
    {
        *list = new;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
/* redir_clear:
**	Frees an entire linked list of redirections (t_redir),
**	including:
**	- The file string
**	- The redirection nodes themselves
**
**	Used during cleanup to avoid memory leaks.
*/
void redir_clear(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next;
        free(redir->file);
        free(redir);
        redir = tmp;
    }
}