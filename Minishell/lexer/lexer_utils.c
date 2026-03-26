#include "minishell.h"

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

char *strjoin_free(char *s1, char *s2)
{
    char *res;

    res = ft_strjoin(s1, s2);
    free(s1);
    return (res);
}

int operator_length(char *s)
{
    if (!s || !s[0])
        return (0);
    if ((s[0] == '<' || s[0] == '>') && s[1] == s[0])
        return (2);
    if (s[0] == '|' || s[0] == '<' || s[0] == '>')
        return (1);
    return (0);
}

t_token_type	operator_type(char *s)
{
    if (!s || !s[0])
        return (WORD);
	if (s[0] == '|')
		return (PIPE);
	if (s[0] == '<')
	{
		if (s[1] == '<')
			return (HEREDOC);
		return (REDIR_IN);
	}
	if (s[0] == '>')
	{
		if (s[1] == '>')
			return (REDIR_APPEND);
		return (REDIR_OUT);
	}
	return (WORD);
}
