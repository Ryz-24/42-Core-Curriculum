#include "minishell.h"

int is_var_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

static char *append_char(char *buffer, char c)
{
    char *tmp;
    char str[2];

    str[0] = c;
    str[1] = '\0';
    tmp = strjoin_free(buffer, str);
    if (!tmp)
        return (NULL);
    return (tmp);
}

/* expand_string:
**	Processes a string and replaces environment variables
**	with their corresponding values.
**
**	Handles:
**	- $? → replaced with last exit status
**	- $VAR → replaced with environment variable value
**	- $ alone → treated as a normal character
**
**	The function builds a new string dynamically by scanning
**	character by character and appending either literals or
**	expanded values.
**
**	If a variable does not exist, it is replaced with an empty string.
**
**	Returns:
**	- Newly allocated expanded string
**	- NULL on failure
*/
char *expand_string(char *str, char **envp)
{
    int     i;
    int     start;
    char    *buffer;
    char    *name;
    char    *value;
    char    *tmp;

    i = 0;
    buffer = ft_strdup("");
    if (!buffer)
        return (NULL);

    while (str[i])
    {
        if (str[i] == '$')
        {
            // $? case
            if (str[i + 1] == '?')
            {
                value = ft_itoa(g_exit_status);
                if (!value)
                {
                    free(buffer);
                    return (NULL);
                }

                tmp = strjoin_free(buffer, value);
                free(value);
                if (!tmp)
                {
                    free(buffer);
                    return (NULL);
                }

                buffer = tmp;
                i += 2;
            }
            // $VAR case
            else if (is_var_char(str[i + 1]))
            {
                i++;
                start = i;

                while (str[i] && is_var_char(str[i]))
                    i++;

                name = ft_substr(str, start, i - start);
                if (!name)
                {
                    free(buffer);
                    return (NULL);
                }

                value = get_env_value(name, envp);
                free(name);

                if (!value)
                    value = ft_strdup("");
                if (!value)
                {
                    free(buffer);
                    return (NULL);
                }

                tmp = strjoin_free(buffer, value);
                free(value);
                if (!tmp)
                {
                    free(buffer);
                    return (NULL);
                }

                buffer = tmp;
            }
            // "$" alone
            else
            {
                tmp = append_char(buffer, str[i]);
                if (!tmp)
                {
                    free(buffer);
                    return (NULL);
                }
                buffer = tmp;
                i++;
            }
        }
        else
        {
            tmp = append_char(buffer, str[i]);
            if (!tmp)
            {
                free(buffer);
                return (NULL);
            }
            buffer = tmp;
            i++;
        }
    }
    return (buffer);
}
/* expand_commands:
**	Applies variable expansion to all commands and their
**	associated redirections.
**
**	Behavior:
**	- Iterates through each command (t_cmd)
**	- Expands each argument unless it was single-quoted
**	- Expands redirection filenames (except HEREDOC delimiters)
**
**	The original strings are replaced with expanded versions.
**
**	On failure, the function returns immediately, leaving
**	cleanup to the caller.
**
**	Returns:
**	- 0 on success
**	- 1 on failure
*/
int expand_commands(t_cmd *cmds, char **envp)
{
    int     i;
    char    *new;
    t_redir *r;

    while (cmds)
    {
        i = 0;
        while (cmds->argv && cmds->argv[i])
        {
            if (cmds->quotes[i] != SINGLE_QUOTE)
            {
                new = expand_string(cmds->argv[i], envp);
                if (!new)
                    return (1);

                free(cmds->argv[i]);
                cmds->argv[i] = new;
            }
            i++;
        }

        r = cmds->redir;
        while (r)
        {
            if (r->type != HEREDOC)
            {
                new = expand_string(r->file, envp);
                if (!new)
                    return (1);

                free(r->file);
                r->file = new;
            }
            r = r->next;
        }

        cmds = cmds->next;
    }
    return (0);
}
