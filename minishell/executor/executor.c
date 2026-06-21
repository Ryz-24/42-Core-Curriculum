#include "minishell.h"

static pid_t fork_pipeline(t_cmd *cmds, int **pipes, int n, char ***envp)
{
	t_cmd *cmd;
	pid_t pid;
	pid_t last_pid;
	int idx[2];

	cmd = cmds;
	idx[0] = 0;
	idx[1] = n;
	last_pid = -1;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			run_child(cmds, pipes, idx, envp);
		last_pid = pid;
		cmd = cmd->next;
		idx[0]++;
	}
	return (last_pid);
}

static int cleanup_pipes_and_fail(int **pipes, int n)
{
	close_pipes(pipes, n);
	free_pipes(pipes, n - 1);
	set_parent_sigint(handle_sigint);
	return (1);
}

static int run_forked(t_cmd *cmds, char ***envp)
{
	int **pipes;
	int n;
	int status;
	pid_t last_pid;

	n = count_cmds(cmds);
	pipes = create_pipes(n);
	if (n > 1 && !pipes)
		return (1);
	set_parent_sigint(SIG_IGN);
	set_parent_sigquit(SIG_IGN);
	last_pid = fork_pipeline(cmds, pipes, n, envp);
	if (last_pid == -1)
		return (cleanup_pipes_and_fail(pipes, n));
	close_pipes(pipes, n);
	free_pipes(pipes, n - 1);
	status = 0;
	if (wait_all(last_pid, &status))
		write(STDOUT_FILENO, "\n", 1);
	set_parent_sigint(handle_sigint);
	set_parent_sigquit(SIG_IGN);
	return (status);
}

int execute_all(t_cmd *cmds, char ***envp)
{
	int n;
	int ret;

	if (!cmds)
		return (0);
	if (open_heredocs(cmds))
		return (g_exit_status);
	n = count_cmds(cmds);
	if (n == 1 && cmds->argv && is_builtin(cmds->argv[0]))
		return (execute_single_builtin(cmds, envp));
	if (n == 1 && is_redir_only(cmds))
		return (run_redir_only(cmds));
	ret = run_forked(cmds, envp);
	close_heredocs(cmds);
	return (ret);
}
