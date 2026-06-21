#include "minishell.h"

void heredoc_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

int heredoc_loop(int write_fd, char *delimiter)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			free(line);
			return (-1);
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n",
						 STDERR_FILENO);
			return (0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		ft_putstr_fd(line, write_fd);
		ft_putchar_fd('\n', write_fd);
		free(line);
	}
}
