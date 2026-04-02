#include "minishell.h"

static char	*get_env(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len)
			&& envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
/*
** builtin_cd:
**	Changes the current working directory of the shell.
**
**	This builtin MUST run in the parent process because
**	changing directory inside a child process would not
**	affect the shell itself.
**
**	Behavior:
**		cd <path>  -> change directory
**		cd         -> change to $HOME
**
**	If HOME is not set and no argument is provided,
**	an error message is printed.
**
**	Errors:
**	- invalid path
**	- permission denied
**
**	Output:
**	Errors printed to STDERR.
**
**	Return value:
**	0 on success
**	1 on failure
*/
int	builtin_cd(char **argv, char ***envp)
{
	char	*path;
	char	cwd[4096];
	char	oldpwd[4096];

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (1);
	if (!argv[1])
		path = get_env("HOME", *envp);
	else
		path = argv[1];
	if (!path)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		update_env_var(envp, "OLDPWD", oldpwd);
		update_env_var(envp, "PWD", cwd);
	}
	return (0);
}