#include "minishell.h"

int alloc_pipes(int **pipes, int count)
{
	int i;

	i = 0;
	while (i < count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			free(pipes[i]);
			free_pipes(pipes, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static char *search_path_dirs(char **dirs, char *cmd)
{
	char *tmp;
	char *full;
	int i;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, F_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

int is_directory(char *path)
{
	struct stat st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

char *get_cmd_path(char **argv, char **envp)
{
	char *path_env;
	char **dirs;
	char *result;

	if (!argv || !argv[0] || !argv[0][0])
		return (NULL);
	if (ft_strchr(argv[0], '/'))
	{
		if (access(argv[0], F_OK) == 0)
			return (ft_strdup(argv[0]));
		return (NULL);
	}
	path_env = get_env_value("PATH", envp);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	free(path_env);
	if (!dirs)
		return (NULL);
	result = search_path_dirs(dirs, argv[0]);
	ft_free_split(dirs);
	return (result);
}
