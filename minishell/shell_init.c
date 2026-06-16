/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:09:28 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/16 13:26:27 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*lex_and_parse(char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	if (check_syntax(tokens))
	{
		token_clear(&tokens);
		g_exit_status = 2;
		return (NULL);
	}
	cmds = parse_tokens(tokens);
	token_clear(&tokens);
	return (cmds);
}

static char	*read_full_line(char *first)
{
	char	*line;
	char	*tmp;
	char	*joined;

	line = ft_strdup(first);
	if (!line)
		return (NULL);
	while (check_quotes(line) == 1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		joined = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(joined, tmp);
		free(joined);
		free(tmp);
		if (!line)
			return (NULL);
	}
	return (line);
}

void	process_input(char *first, char ***envp)
{
	char	*line;
	t_cmd	*cmds;

	line = read_full_line(first);
	if (!line)
		return ;
	cmds = lex_and_parse(line);
	free(line);
	if (!cmds)
		return ;
	if (expand_commands(cmds, *envp))
	{
		cmd_clear(&cmds);
		g_exit_status = 1;
		return ;
	}
	g_exit_status = execute_all(cmds, envp);
	cmd_clear(&cmds);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			ft_free_split(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}
