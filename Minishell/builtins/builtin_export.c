#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_env_index(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	add_env(char ***envp, char *new_var)
{
	int		size;
	char	**new_env;
	int		i;

	size = 0;
	while ((*envp)[size])
		size++;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return ;

	i = 0;
	while (i < size)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i++] = ft_strdup(new_var);
	new_env[i] = NULL;

	free(*envp);
	*envp = new_env;
}

static void	update_env(char ***envp, int index, char *var)
{
	free((*envp)[index]);
	(*envp)[index] = ft_strdup(var);
}

/*
** builtin_export:
**	Adds or updates environment variables.
**
**	Supported forms:
**
**		export KEY=value
**			-> adds new variable or updates existing one
**
**		export
**			-> prints environment variables
**
**	Validation:
**	Variable name must:
**	- start with alphabetic character or '_'
**	- contain only alphanumeric characters or '_'
**
**	If identifier is invalid:
**		error message printed to STDERR
**		exit status becomes 1
**
**	Implementation logic:
**	1) validate identifier
**	2) split KEY from VALUE
**	3) search existing environment
**	4) update existing OR append new variable
**
**	The environment array may be reallocated.
**
**	Return value:
**	0 if all valid
**	1 if any invalid identifier detected
*/
int	builtin_export(char **argv, char ***envp)
{
	int		i;
	int		index;
	char	*equal;
	char	*key;
	int		status;

	if (!argv[1])
		return (builtin_env(*envp));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			status = 1;
			i++;
			continue ;
		}
		equal = ft_strchr(argv[i], '=');
		if (equal)
		{
			key = ft_substr(argv[i], 0, equal - argv[i]);
			index = find_env_index(*envp, key);
			if (index >= 0)
				update_env(envp, index, argv[i]);
			else
				add_env(envp, argv[i]);
			free(key);
		}
		i++;
	}
	return (status);
}