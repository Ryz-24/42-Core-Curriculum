/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:02:49 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:08:48 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	set_env_var(char ***envp, char *arg)
{
	char	*equal;
	char	*key;
	int		index;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return ;
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return ;
	index = find_env_index(*envp, key);
	free(key);
	if (index >= 0)
	{
		free((*envp)[index]);
		(*envp)[index] = ft_strdup(arg);
	}
	else
		add_env(envp, arg);
}

int	builtin_export(char **argv, char ***envp)
{
	int	i;
	int	status;

	if (!argv[1])
		return (builtin_env(*envp));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		else
			set_env_var(envp, argv[i]);
		i++;
	}
	return (status);
}
