/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:45:05 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/16 15:46:56 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_line(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
}

static void	heredoc_child_loop(char *delimiter, int write_fd)
{
	char	*line;

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
		write_heredoc_line(write_fd, line);
		free(line);
	}
}

void	heredoc_child(char *delimiter, int write_fd)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	heredoc_child_loop(delimiter, write_fd);
	close(write_fd);
	exit(0);
}

int	heredoc_parent(int *pipefd, pid_t pid,
				struct sigaction *sa_old)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, sa_old, NULL);
	if (WIFSIGNALED(status))
	{
		g_exit_status = 130;
		close(pipefd[0]);
		write(STDOUT_FILENO, "\n", 1);
		return (-1);
	}
	return (pipefd[0]);
}
