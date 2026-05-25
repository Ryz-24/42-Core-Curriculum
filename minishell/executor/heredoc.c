/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:14:43 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/25 13:28:53 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_line(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
}

int	read_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n",
				STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipefd[1], line);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
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
