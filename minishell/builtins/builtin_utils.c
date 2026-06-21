#include "minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int execute_builtin(t_cmd *cmd, t_cmd *head, char ***envp)
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
		return (builtin_exit(cmd->argv, &head, envp));
	return (1);
}

static void append_env(char ***envp, char *entry, int size)
{
	char **new_env;
	int i;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(entry);
		return;
	}
	i = 0;
	while (i < size)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i++] = entry;
	new_env[i] = NULL;
	free(*envp);
	*envp = new_env;
}

static void set_or_add(char ***envp, char *entry, int klen, int size)
{
	int i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], entry, klen) == 0 && (*envp)[i][klen] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = entry;
			return;
		}
		i++;
	}
	append_env(envp, entry, size);
}

void update_env_var(char ***envp, char *key, char *value)
{
	char *entry;
	char *tmp;
	int size;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return;
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return;
	size = 0;
	while ((*envp)[size])
		size++;
	set_or_add(envp, entry, ft_strlen(key), size);
}
