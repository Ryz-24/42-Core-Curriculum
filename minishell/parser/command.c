/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:50:55 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/17 16:36:02 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->quotes = NULL;
	cmd->redir = NULL;
	cmd->pipe_to_next = 0;
	cmd->next = NULL;
	return (cmd);
}

static int	alloc_arrays(int len, char ***nargv, t_quote_type **nquotes)
{
	*nargv = malloc(sizeof(char *) * (len + 2));
	*nquotes = malloc(sizeof(t_quote_type) * (len + 1));
	if (!*nargv || !*nquotes)
	{
		free(*nargv);
		free(*nquotes);
		return (1);
	}
	return (0);
}

static void	swap_arrays(t_cmd *cmd, char **nargv, t_quote_type *nquotes)
{
	free(cmd->argv);
	free(cmd->quotes);
	cmd->argv = nargv;
	cmd->quotes = nquotes;
}

static void	copy_old_arrays(t_cmd *cmd, char **nargv, t_quote_type *nquotes,
		int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		nargv[i] = cmd->argv[i];
		nquotes[i] = cmd->quotes[i];
		i++;
	}
}

int	cmd_add_arg(t_cmd *cmd, char *arg, t_quote_type quote)
{
	int				len;
	char			**nargv;
	t_quote_type	*nquotes;

	len = argv_len(cmd->argv);
	if (alloc_arrays(len, &nargv, &nquotes))
		return (1);
	copy_old_arrays(cmd, nargv, nquotes, len);
	nargv[len] = ft_strdup(arg);
	if (!nargv[len])
	{
		free(nargv);
		free(nquotes);
		return (1);
	}
	nquotes[len] = quote;
	nargv[len + 1] = NULL;
	swap_arrays(cmd, nargv, nquotes);
	return (0);
}
