#include "minishell.h"

static int match_var(char *env, char *name)
{
	int len;

	len = ft_strlen(name);
	if (!ft_strncmp(env, name, len) && env[len] == '=')
		return (1);
	return (0);
}

/*
** builtin_unset:
**	Removes variables from the shell environment.
**
**	For each argument:
**		unset VAR
**
**	The function searches the environment array and removes
**	the matching entry.
**
**	Implementation detail:
**	- matching variable is freed
**	- remaining variables are shifted left
**		A B C D
**			↓ remove B
**		A C D
**		Move elements left.
**	- environment stays NULL-terminated
**
**	Important:
**	The environment array itself is modified.
**
**	Return value:
**	Always returns 0 (bash behavior).
*/
int builtin_unset(char **argv, char ***envp)
{
	int i;
	int j;
	int k;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			if (match_var((*envp)[j], argv[i]))
			{
				free((*envp)[j]);
				k = j;
				while ((*envp)[k])
				{
					(*envp)[k] = (*envp)[k + 1];
					k++;
				}
				break;
			}
			j++;
		}
		i++;
	}
	return (0);
}