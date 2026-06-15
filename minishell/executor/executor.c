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
	exec_cmd(path, cmd, envp);
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

static void	set_parent_sigint(void (*handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (handler == handle_sigint)
		sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static int	run_forked(t_cmd *cmds, char ***envp)
{
	int		**pipes;
	int		n;
	int		status;

	n = count_cmds(cmds);
	pipes = create_pipes(n);
	if (n > 1 && !pipes)
		return (1);
	set_parent_sigint(SIG_IGN);
	if (fork_pipeline(cmds, pipes, n, envp))
		return (close_pipes(pipes, n), free_pipes(pipes, n - 1),
			set_parent_sigint(handle_sigint), 1);
	close_pipes(pipes, n);
	free_pipes(pipes, n - 1);
	status = 0;
	wait_all(&status);
	if (g_exit_status == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	set_parent_sigint(handle_sigint);
	return (status);
}

int	execute_all(t_cmd *cmds, char ***envp)
{
	int	n;

	if (!cmds)
		return (0);
	if (open_heredocs(cmds))
		return (1);
	n = count_cmds(cmds);
	if (n == 1 && cmds->argv && is_builtin(cmds->argv[0]))
		return (execute_single_builtin(cmds, envp));
	if (n == 1 && is_redir_only(cmds))
		return (run_redir_only(cmds));
	return (run_forked(cmds, envp));
}
