#include "minishell.h"

int read_heredoc(char *delimiter)
{
	int pipefd[2];
	int saved;
	int ret;

	if (pipe(pipefd) == -1)
		return (-1);
	saved = dup(STDIN_FILENO);
	g_exit_status = 0;
	set_parent_sigint(heredoc_sigint);
	ret = heredoc_loop(pipefd[1], delimiter);
	close(pipefd[1]);
	dup2(saved, STDIN_FILENO);
	close(saved);
	set_parent_sigint(handle_sigint);
	if (ret == -1)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}

static int process_heredoc(t_redir *r)
{
	char *tmp;
	int fd;

	tmp = strip_quotes(r->file);
	if (!tmp)
		return (-1);
	free(r->file);
	r->file = tmp;
	fd = read_heredoc(r->file);
	if (fd == -1)
		return (-1);
	r->heredoc_fd = fd;
	return (0);
}

int open_heredocs(t_cmd *cmds)
{
	t_cmd *cmd;
	t_redir *r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			if (r->type == HEREDOC && process_heredoc(r) == -1)
				return (1);
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void close_heredocs(t_cmd *cmds)
{
	t_cmd *cmd;
	t_redir *r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			if (r->type == HEREDOC && r->heredoc_fd >= 0)
			{
				close(r->heredoc_fd);
				r->heredoc_fd = -1;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}
