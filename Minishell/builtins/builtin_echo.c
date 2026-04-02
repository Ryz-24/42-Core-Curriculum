#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}
/*
** builtin_echo:
**	Implements the bash echo builtin.
**
**	Prints its arguments separated by spaces.
**
**	Supported option:
**		-n   -> suppress trailing newline
**		multiple -n flags are accepted (echo -n -n hello)
**
**	Behavior:
**		echo hello world
**			-> prints "hello world\n"
**
**		echo -n hello
**			-> prints "hello world"
**
**	Notes:
**	- Output is written to STDOUT.
**	- Redirections are handled by executor before calling this.
**
**	Return value:
**	Always returns 0.
*/
int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}