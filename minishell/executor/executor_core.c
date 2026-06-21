#include "minishell.h"

static void restore_std(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

int execute_single_builtin(t_cmd *cmd, char ***envp)
{
	int saved_in;
	int saved_out;
	int ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redir))
	{
		restore_std(saved_in, saved_out);
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		restore_std(saved_in, saved_out);
		return (execute_builtin(cmd, cmd, envp));
	}
	ret = execute_builtin(cmd, cmd, envp);
	restore_std(saved_in, saved_out);
	return (ret);
}

int run_redir_only(t_cmd *cmd)
{
	int saved_in;
	int saved_out;
	int ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	ret = apply_redirections(cmd->redir);
	restore_std(saved_in, saved_out);
	return (ret);
}

static void exec_error_exit(char *path, t_cmd *head, char ***envp, int code)
{
	free(path);
	if (head)
		cmd_clear(&head);
	if (envp && *envp)
	{
		ft_free_split(*envp);
		*envp = NULL;
	}
	rl_clear_history();
	exit(code);
}

void exec_cmd(char *path, t_cmd *cmd, t_cmd *head, char ***envp)
{
	if (is_directory(path))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		exec_error_exit(path, head, envp, 126);
	}
	execve(path, cmd->argv, *envp);
	perror(path);
	exec_error_exit(path, head, envp, 126);
}
