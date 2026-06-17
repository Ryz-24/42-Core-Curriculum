/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:51:04 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:07:14 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_word(t_cmd *curr, t_token *token, t_cmd **head)
{
	if (cmd_add_arg(curr, token->value, token->quote))
	{
		cmd_clear(head);
		return (1);
	}
	return (0);
}

static int	handle_pipe(t_cmd **curr, t_cmd **head)
{
	(*curr)->pipe_to_next = 1;
	(*curr)->next = cmd_new();
	if (!(*curr)->next)
	{
		cmd_clear(head);
		return (1);
	}
	*curr = (*curr)->next;
	return (0);
}

static int	handle_redir(t_cmd *curr, t_token **tok, t_cmd **head)
{
	t_token_type	type;
	t_redir			*redir;

	type = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != WORD)
	{
		cmd_clear(head);
		return (1);
	}
	redir = redir_new(type, (*tok)->value);
	if (!redir)
	{
		cmd_clear(head);
		return (1);
	}
	redir_add_back(&curr->redir, redir);
	return (0);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;

	if (!tokens)
		return (NULL);
	head = cmd_new();
	if (!head)
		return (NULL);
	curr = head;
	while (tokens)
	{
		if (tokens->type == WORD && handle_word(curr, tokens, &head))
			return (NULL);
		else if (is_redirection(tokens->type)
			&& handle_redir(curr, &tokens, &head))
			return (NULL);
		else if (tokens->type == PIPE && handle_pipe(&curr, &head))
			return (NULL);
		tokens = tokens->next;
	}
	return (head);
}
