/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:08:18 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:08:19 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_builtin(t_cmd *cmd, char ***envp)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redir))
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	ret = execute_builtin(cmd, envp);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (ret);
}

int	run_redir_only(t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	ret = apply_redirections(cmd->redir);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (ret);
}

/*
** exec_cmd:
**	Final step of child execution after path is resolved.
**	Checks for directory before calling execve to match bash error message.
**	"Is a directory" instead of "Permission denied" for ./ . / etc.
*/
void	exec_cmd(char *path, t_cmd *cmd, char ***envp)
{
	if (is_directory(path))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		exit(126);
	}
	execve(path, cmd->argv, *envp);
	perror(path);
	exit(126);
}
