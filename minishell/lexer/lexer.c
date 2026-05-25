/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:52:43 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/25 14:35:28 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_quoted(char *input, int *i, t_quote_type *quote)
{
	char	q;
	int		start;
	char	*str;

	q = input[*i];
	if (q == '\'')
		*quote = SINGLE_QUOTE;
	else
		*quote = DOUBLE_QUOTE;
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != q)
		(*i)++;
	str = ft_substr(input, start, *i - start);
	if (!str)
		return (NULL);
	if (input[*i] == q)
		(*i)++;
	return (str);
}

char	*read_word(char *input, int *i, t_quote_type *quote)
{
	char			*buf;
	char			*piece;
	t_quote_type	q;

	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	*quote = NO_QUOTE;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
	{
		q = NO_QUOTE;
		if (input[*i] == '\'' || input[*i] == '"')
			piece = read_quoted(input, i, &q);
		else
			piece = ft_substr(input, (*i)++, 1);
		if (!piece)
			return (free(buf), NULL);
		if (q != NO_QUOTE && *quote == NO_QUOTE)
			*quote = q;
		buf = strjoin_free(buf, piece);
		free(piece);
		if (!buf)
			return (NULL);
	}
	return (buf);
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

static t_token	*word_token(char *input, int *i, t_token **list)
{
	t_token			*tok;
	char			*word;
	t_quote_type	q;

	word = read_word(input, i, &q);
	if (!word)
		return (token_clear(list), NULL);
	tok = token_create(WORD, word, q);
	free(word);
	return (tok);
}

t_token	*lexer(char *input)
{
	int		i;
	t_token	*tokens;
	t_token	*token;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			token = create_operator_token(input, &i);
		else
			token = word_token(input, &i, &tokens);
		if (!token)
			return (token_clear(&tokens), NULL);
		token_add_back(&tokens, token);
	}
	return (tokens);
}
