#include "minishell.h"

static void child_exit(t_cmd *head, char ***envp, int code)
{
	cmd_clear(&head);
	ft_free_split(*envp);
	exit(code);
}

static void run_child(t_cmd *cmd, t_cmd *head, int **pipes,
					  int *idx, char ***envp)
{
	char *path;

	reset_child_signals();
	setup_child_pipes(pipes, idx[0], idx[1]);
	free_pipes(pipes, idx[1] - 1);
	if (apply_redirections(cmd->redir))
		child_exit(head, envp, 1);
	if (is_builtin(cmd->argv[0]))
		child_exit(head, envp, execute_builtin(cmd, head, envp));
	path = get_cmd_path(cmd->argv, *envp);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		child_exit(head, envp, 127);
	}
	exec_cmd(path, cmd, head, envp);
}

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
			run_child(cmd, cmds, pipes, idx, envp);
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
