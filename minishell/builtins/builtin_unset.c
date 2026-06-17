/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:02:58 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:08:43 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_var(char *env, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (!ft_strncmp(env, name, len) && env[len] == '=')
		return (1);
	return (0);
}

static void	remove_env_entry(char ***envp, int j)
{
	int	k;

	free((*envp)[j]);
	k = j;
	while ((*envp)[k])
	{
		(*envp)[k] = (*envp)[k + 1];
		k++;
	}
}

int	builtin_unset(char **argv, char ***envp)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			if (match_var((*envp)[j], argv[i]))
			{
				remove_env_entry(envp, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
