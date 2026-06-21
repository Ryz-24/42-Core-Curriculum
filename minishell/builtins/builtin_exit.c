#include "minishell.h"

static int is_numeric(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void clean_exit(t_cmd **cmds, char ***envp, int status)
{
	if (cmds)
		cmd_clear(cmds);
	if (envp && *envp)
	{
		ft_free_split(*envp);
		*envp = NULL;
	}
	rl_clear_history();
	exit((unsigned char)status);
}

int builtin_exit(char **argv, t_cmd **cmds, char ***envp)
{
	int status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
		clean_exit(cmds, envp, g_exit_status);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		clean_exit(cmds, envp, 2);
	}
	if (argv[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	status = ft_atoi(argv[1]);
	clean_exit(cmds, envp, status);
	return (0);
}
