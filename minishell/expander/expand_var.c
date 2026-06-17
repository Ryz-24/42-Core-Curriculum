/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 16:53:09 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/17 16:54:58 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(char *str, int *i, char **envp)
{
	int		start;
	char	*name;
	char	*value;

	(*i)++;
	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	if (!name)
		return (NULL);
	value = get_env_value(name, envp);
	free(name);
	if (!value)
		value = ft_strdup("");
	return (value);
}

char	*expand_var(char *str, char *buf, int *i, char **envp)
{
	char	*value;

	value = get_var_value(str, i, envp);
	if (!value)
	{
		free(buf);
		return (NULL);
	}
	buf = strjoin_free(buf, value);
	free(value);
	return (buf);
}
