/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:14:43 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/16 15:45:33 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(char *delimiter)
{
	int					pipefd[2];
	pid_t				pid;
	struct sigaction	sa_ign;
	struct sigaction	sa_old;

	if (pipe(pipefd) == -1)
		return (-1);
	ft_memset(&sa_ign, 0, sizeof(sa_ign));
	sa_ign.sa_handler = SIG_IGN;
	sigemptyset(&sa_ign.sa_mask);
	sigaction(SIGINT, &sa_ign, &sa_old);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		sigaction(SIGINT, &sa_old, NULL);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(delimiter, pipefd[1]);
	return (heredoc_parent(pipefd, pid, &sa_old));
}

int	open_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*r;
	int		fd;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			if (r->type == HEREDOC)
			{
				fd = read_heredoc(r->file);
				if (fd == -1)
					return (1);
				r->heredoc_fd = fd;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	close_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			if (r->type == HEREDOC && r->heredoc_fd >= 0)
			{
				close(r->heredoc_fd);
				r->heredoc_fd = -1;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}
