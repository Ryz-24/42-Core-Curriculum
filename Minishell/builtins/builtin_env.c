#include "minishell.h"

/*
** builtin_env:
**	Prints all environment variables.
**  Environment = array of strings.
**
**	The environment is stored as:
**		char **envp
**
**	Each entry has format:
**		KEY=value
**
**	Output goes to STDOUT.
**
**	Note:
**	This implementation prints variables exactly as stored.
**
**	Return value:
**	Always returns 0.
*/
int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}