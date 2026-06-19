#include "minishell.h"

t_token	*token_create(t_token_type type, char *value, t_quote_type quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->quote = quote;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **list, t_token *tokn)
{
	t_token	*tmp;

	if (!list || !tokn)
		return ;
	if (*list == NULL)
	{
		*list = tokn;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tokn;
}

void	token_clear(t_token **list)
{
	t_token	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
}

t_token	*create_operator_token(char *input, int *i)
{
	int				len;
	char			*op;
	t_token			*token;
	t_token_type	type;

	len = operator_length(&input[*i]);
	if (len <= 0)
		return (NULL);
	op = ft_substr(input, *i, len);
	if (!op)
		return (NULL);
	type = operator_type(op);
	token = token_create(type, op, NO_QUOTE);
	free(op);
	if (!token)
		return (NULL);
	*i += len;
	return (token);
}
