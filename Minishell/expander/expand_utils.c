#include "minishell.h"

char *get_env_value(char *name, char **envp)
{
    int     i;
    int     len;

    if (!name || !envp)
        return (NULL);

    len = ft_strlen(name);
    i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0
            && envp[i][len] == '=')
        {
            return (ft_strdup(envp[i] + len + 1));
        }
        i++;
    }
    return (NULL);
}