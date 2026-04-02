#include "minishell.h"

/*
** builtin_pwd:
**	Prints the absolute path of the current working directory.
**
**	Uses getcwd() to retrieve directory path.
**
**	Output is written to STDOUT.
**
**	If getcwd fails, perror is used to display the system error.
**
**	Return value:
**	0 on success
**	1 on error
*/
int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	perror("pwd");
	return (1);
}