#include "minishell.h"

static void child_exit(t_cmd *head, char ***envp, int code)
{
	cmd_clear(&head);
	ft_free_split(*envp);
	exit(code);
}

void run_child(t_cmd *head, int **pipes, int *idx, char ***envp)
{
	t_cmd *cmd;
	char *path;
	int i;

	cmd = head;
	i = -1;
	while (++i < idx[0])
		cmd = cmd->next;
	reset_child_signals();
	setup_child_pipes(pipes, idx[0], idx[1]);
	free_pipes(pipes, idx[1] - 1);
	if (apply_redirections(cmd->redir))
		child_exit(head, envp, 1);
	if (!cmd->argv || !cmd->argv[0])
		child_exit(head, envp, 0);
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
