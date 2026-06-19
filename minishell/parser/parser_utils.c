#include "minishell.h"

int	argv_len(char **argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	is_redir_only(t_cmd *cmd)
{
	return (!cmd->argv && cmd->redir);
}

void	cmd_clear(t_cmd **cmds)
{
	t_cmd	*tmp;
	int		i;

	while (*cmds)
	{
		tmp = (*cmds)->next;
		if ((*cmds)->argv)
		{
			i = 0;
			while ((*cmds)->argv[i])
			{
				free((*cmds)->argv[i]);
				i++;
			}
			free((*cmds)->argv);
		}
		redir_clear((*cmds)->redir);
		free((*cmds)->quotes);
		free(*cmds);
		*cmds = tmp;
	}
}
