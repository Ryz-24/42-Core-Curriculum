/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:52:43 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/17 16:41:00 by rzaatreh         ###   ########.fr       */
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

static char	*append_piece(char **buf, char *input, int *i, t_quote_type *quote)
{
	char			*piece;
	t_quote_type	q;

	q = NO_QUOTE;
	if (input[*i] == '\'' || input[*i] == '"')
		piece = read_quoted(input, i, &q);
	else
		piece = ft_substr(input, (*i)++, 1);
	if (!piece)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	if (q != NO_QUOTE && *quote == NO_QUOTE)
		*quote = q;
	*buf = strjoin_free(*buf, piece);
	free(piece);
	return (*buf);
}

char	*read_word(char *input, int *i, t_quote_type *quote)
{
	char	*buf;

	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	*quote = NO_QUOTE;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
	{
		if (!append_piece(&buf, input, i, quote))
			return (NULL);
	}
	return (buf);
}

static t_token	*word_token(char *input, int *i, t_token **list)
{
	t_token			*tok;
	char			*word;
	t_quote_type	q;

	word = read_word(input, i, &q);
	if (!word)
	{
		token_clear(list);
		return (NULL);
	}
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
		{
			token_clear(&tokens);
			return (NULL);
		}
		token_add_back(&tokens, token);
	}
	return (tokens);
}
