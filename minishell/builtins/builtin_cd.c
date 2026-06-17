/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:02:36 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:08:59 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(char **envp)
{
	int		i;
	int		len;

	len = ft_strlen("HOME");
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME", len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	update_pwd(char ***envp, char *oldpwd)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	update_env_var(envp, "OLDPWD", oldpwd);
	update_env_var(envp, "PWD", cwd);
	return (0);
}

int	builtin_cd(char **argv, char ***envp)
{
	char	*path;
	char	oldpwd[4096];

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (1);
	if (!argv[1])
		path = get_home(*envp);
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
	return (update_pwd(envp, oldpwd));
}
