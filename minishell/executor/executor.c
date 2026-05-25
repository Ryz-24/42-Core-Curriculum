/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:07:29 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/25 14:34:44 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** run_child:
**	idx[0] = index of this command in pipeline
**	idx[1] = total number of commands
**	Bundles both into one array to stay within 4-argument limit.
*/
static void	run_child(t_cmd *cmd, int **pipes, int *idx, char ***envp)
{
	char	*path;

	reset_child_signals();
	setup_child_pipes(pipes, idx[0], idx[1]);
	if (apply_redirections(cmd->redir))
		exit(1);
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, envp));
	path = get_cmd_path(cmd->argv, *envp);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->argv, *envp);
	perror(path);
	free(path);
	exit(126);
}

static int	fork_pipeline(t_cmd *cmds, int **pipes, int n, char ***envp)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		idx[2];

	cmd = cmds;
	idx[0] = 0;
	idx[1] = n;
	while (cmd)
	{
		if (!cmd->argv)
		{
			cmd = cmd->next;
			idx[0]++;
			continue ;
		}
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			run_child(cmd, pipes, idx, envp);
		cmd = cmd->next;
		idx[0]++;
	}
	return (0);
}

int	execute_pipeline(t_cmd *cmds, char ***envp)
{
	int		n;
	int		**pipes;
	int		last_status;

	n = count_cmds(cmds);
	if (n == 1 && cmds->argv && is_builtin(cmds->argv[0]))
		return (execute_single_builtin(cmds, envp));
	if (n == 1 && is_redir_only(cmds))
		return (run_redir_only(cmds));
	pipes = create_pipes(n);
	if (n > 1 && !pipes)
		return (1);
	if (fork_pipeline(cmds, pipes, n, envp))
	{
		close_pipes(pipes, n);
		free_pipes(pipes, n - 1);
		return (1);
	}
	close_pipes(pipes, n);
	free_pipes(pipes, n - 1);
	last_status = 0;
	wait_all(&last_status);
	return (last_status);
}

int	execute_all(t_cmd *cmds, char ***envp)
{
	int	status;

	if (!cmds)
		return (0);
	if (open_heredocs(cmds))
	{
		g_exit_status = 1;
		return (1);
	}
	status = execute_pipeline(cmds, envp);
	g_exit_status = status;
	return (status);
}
