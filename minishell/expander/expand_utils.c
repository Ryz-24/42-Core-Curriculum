/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:02:15 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:02:17 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, char **envp)
{
	int		i;
	int		len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

static int	expand_argv(t_cmd *cmd, char **envp)
{
	int		i;
	char	*new;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (cmd->quotes[i] != SINGLE_QUOTE)
		{
			new = expand_string(cmd->argv[i], envp);
			if (!new)
				return (1);
			free(cmd->argv[i]);
			cmd->argv[i] = new;
		}
		i++;
	}
	return (0);
}

static int	expand_redirs(t_cmd *cmd, char **envp)
{
	t_redir	*r;
	char	*new;

	r = cmd->redir;
	while (r)
	{
		if (r->type != HEREDOC)
		{
			new = expand_string(r->file, envp);
			if (!new)
				return (1);
			free(r->file);
			r->file = new;
		}
		r = r->next;
	}
	return (0);
}

/*
** expand_commands:
**	Applies variable expansion to all commands and redirections.
**	Skips single-quoted args and HEREDOC delimiters.
**
**	Returns 0 on success, 1 on failure.
*/
int	expand_commands(t_cmd *cmds, char **envp)
{
	while (cmds)
	{
		if (expand_argv(cmds, envp))
			return (1);
		if (expand_redirs(cmds, envp))
			return (1);
		cmds = cmds->next;
	}
	return (0);
}
