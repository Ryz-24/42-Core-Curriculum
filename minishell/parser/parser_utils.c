/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:50:59 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/25 13:33:53 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_len(char **argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	is_redir_only(t_cmd *cmd)
{
	return (!cmd->argv && cmd->redir);
}

void	cmd_clear(t_cmd **cmds)
{
	t_cmd	*tmp;
	int		i;

	while (*cmds)
	{
		tmp = (*cmds)->next;
		if ((*cmds)->argv)
		{
			i = 0;
			while ((*cmds)->argv[i])
			{
				free((*cmds)->argv[i]);
				i++;
			}
			free((*cmds)->argv);
		}
		redir_clear((*cmds)->redir);
		free((*cmds)->quotes);
		free(*cmds);
		*cmds = tmp;
	}
}
