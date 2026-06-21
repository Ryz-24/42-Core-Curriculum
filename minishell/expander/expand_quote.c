#include "minishell.h"

static int	handle_quote(char c, char *state)
{
	if (c == '\'' && *state != '"')
	{
		if (*state == '\'')
			*state = 0;
		else
			*state = '\'';
		return (1);
	}
	if (c == '"' && *state != '\'')
	{
		if (*state == '"')
			*state = 0;
		else
			*state = '"';
		return (1);
	}
	return (0);
}

static char	*append_char_inc(char *buf, char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	return (append_char(buf, c));
}

static char	*expand_step(char *str, char *buf, int *i, char **envp)
{
	if (str[*i] == '$' && str[*i + 1] == '?')
		return (expand_dollar(buf, i));
	if (str[*i] == '$' && str[*i + 1] && is_var_char(str[*i + 1]))
		return (expand_var(str, buf, i, envp));
	return (append_char_inc(buf, str, i));
}

char	*expand_string(char *str, char **envp)
{
	int		i;
	char	*buf;
	char	state;

	i = 0;
	state = 0;
	buf = ft_strdup("");
	while (buf && str[i])
	{
		if (handle_quote(str[i], &state))
			i++;
		else if (state == '\'')
			buf = append_char_inc(buf, str, &i);
		else
			buf = expand_step(str, buf, &i, envp);
	}
	return (buf);
}
