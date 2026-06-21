#include "minishell.h"

char	*strip_quotes(char *str)
{
	int		i;
	int		j;
	char	q;
	char	*res;

	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	q = 0;
	while (str[i])
	{
		if (q == 0 && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q != 0 && str[i] == q)
			q = 0;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	if (!input)
		return (1);
	i = 0;
	quote = 0;
	while (input[i])
	{
		if (quote == 0 && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (quote != 0 && input[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}
