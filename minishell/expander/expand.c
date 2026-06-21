#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*append_char(char *buffer, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (strjoin_free(buffer, str));
}

char	*expand_dollar(char *buffer, int *i)
{
	char	*value;
	char	*tmp;

	value = ft_itoa(g_exit_status);
	if (!value)
	{
		free(buffer);
		return (NULL);
	}
	tmp = strjoin_free(buffer, value);
	free(value);
	*i += 2;
	return (tmp);
}

