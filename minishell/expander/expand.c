/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:02:01 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/17 16:53:30 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*append_char(char *buffer, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (strjoin_free(buffer, str));
}

static char	*expand_dollar(char *buffer, int *i)
{
	char	*value;
	char	*tmp;

	value = ft_itoa(g_exit_status);
	if (!value)
	{
		free(buffer);
		return (NULL);
	}
	tmp = strjoin_free(buffer, value);
	free(value);
	*i += 2;
	return (tmp);
}

char	*expand_string(char *str, char **envp)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			buffer = expand_dollar(buffer, &i);
		else if (str[i] == '$' && str[i + 1] && is_var_char(str[i + 1]))
			buffer = expand_var(str, buffer, &i, envp);
		else
		{
			buffer = append_char(buffer, str[i]);
			i++;
		}
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}
