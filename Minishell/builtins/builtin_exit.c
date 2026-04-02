#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** builtin_exit:
**	Terminates the minishell program.
**
**	Behavior:
**		exit
**			-> exits using last exit status (g_exit_status)
**
**		exit <number>
**			-> exits with provided status
**
**	This builtin must execute in the parent process
**	when no pipeline exists.
**
**	Execution never returns because exit() terminates
**	the program immediately.
*/
int	builtin_exit(char **argv)
{
	int	status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!argv[1])
		exit(g_exit_status);
	if (!is_numeric(argv[1]))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (argv[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	status = ft_atoi(argv[1]);
	exit(status);
}