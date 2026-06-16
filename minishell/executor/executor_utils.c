#include "minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int		n;
	t_cmd	*tmp;

	n = 0;
	tmp = cmds;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

int	**create_pipes(int count)
{
	int	**pipes;

	if (count <= 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	if (!alloc_pipes(pipes, count))
	{
		free(pipes);
		return (NULL);
	}
	return (pipes);
}

void	close_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

/*
** wait_all:
**	Waits for all children. Only tracks exit status of last_pid
**	(rightmost command = bash pipeline $? behavior).
**	Returns 1 if last child was killed by a signal (so caller
**	can print a newline), 0 otherwise.
*/
int	wait_all(pid_t last_pid, int *last_status)
{
	int		status;
	pid_t	pid;
	int		signaled;

	signaled = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid != last_pid)
			continue ;
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			*last_status = 128 + WTERMSIG(status);
			signaled = 1;
		}
	}
	return (signaled);
}
