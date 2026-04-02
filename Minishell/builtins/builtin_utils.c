#include "minishell.h"

/*
** is_builtin:
**	Checks whether the given command name corresponds to one of the
**	shell builtins.
**
**	This function is used by the executor BEFORE deciding whether to:
**		1) execute a builtin directly, or
**		2) search PATH and call execve().
**
**	If the command matches one of:
**		echo, cd, pwd, export, unset, env, exit
**	the function returns 1.
**
**	Otherwise returns 0 meaning the command must be executed as an
**	external program.
**
**	Important:
**	This function DOES NOT execute anything.
**	It only identifies command type.
*/
int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (!ft_strcmp(cmd, "echo"))
        return (1);
    if (!ft_strcmp(cmd, "cd"))
        return (1);
    if (!ft_strcmp(cmd, "pwd"))
        return (1);
    if (!ft_strcmp(cmd, "export"))
        return (1);
    if (!ft_strcmp(cmd, "unset"))
        return (1);
    if (!ft_strcmp(cmd, "env"))
        return (1);
    if (!ft_strcmp(cmd, "exit"))
        return (1);
    return (0);
}

/*
** execute_builtin:
**	Dispatches execution to the correct builtin implementation.
**
**	The executor calls this after detecting that the command is a
**	builtin.
**
**	Input:
**		cmd   -> parsed command node
**		envp  -> address of environment array (modifiable)
**
**	Why char ***envp ?
**	Builtins like export/unset must modify the shell environment,
**	so the environment pointer itself may change.
**
**	Returns:
**		exit status of executed builtin.
**
**	Execution rule:
**	- Builtins executed WITHOUT pipes must run in parent process.
**	- Builtins inside pipelines run in child processes.
*/
int execute_builtin(t_cmd *cmd, char ***envp)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);

    if (!ft_strcmp(cmd->argv[0], "echo"))
        return (builtin_echo(cmd->argv));
    if (!ft_strcmp(cmd->argv[0], "cd"))
        return (builtin_cd(cmd->argv, envp));
    if (!ft_strcmp(cmd->argv[0], "pwd"))
        return (builtin_pwd());
    if (!ft_strcmp(cmd->argv[0], "export"))
        return (builtin_export(cmd->argv, envp));
    if (!ft_strcmp(cmd->argv[0], "unset"))
        return (builtin_unset(cmd->argv, envp));
    if (!ft_strcmp(cmd->argv[0], "env"))
        return (builtin_env(*envp));
    if (!ft_strcmp(cmd->argv[0], "exit"))
        return (builtin_exit(cmd->argv));

    return (1);
}