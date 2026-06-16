/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:07:50 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:07:59 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_redir_in(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd == -1)
	{
		perror(r->file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	apply_redir_out(t_redir *r)
{
	int	flags;
	int	fd;

	if (r->type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(r->file, flags, 0644);
	if (fd == -1)
	{
		perror(r->file);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN && apply_redir_in(redir))
			return (1);
		else if ((redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			&& apply_redir_out(redir))
			return (1);
		else if (redir->type == HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
		redir = redir->next;
	}
	return (0);
}

void	setup_child_pipes(int **pipes, int index, int total)
{
	int	i;

	if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index < total - 1)
		dup2(pipes[index][1], STDOUT_FILENO);
	i = 0;
	while (i < total - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	reset_child_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
