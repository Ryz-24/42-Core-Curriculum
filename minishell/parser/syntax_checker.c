/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:51:09 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 12:59:41 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_err(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

static int	check_pipe(t_token *curr)
{
	if (!curr->next || curr->next->type == PIPE)
		return (syntax_err("|"));
	return (0);
}

static int	check_redir(t_token *curr)
{
	if (!curr->next)
		return (syntax_err("newline"));
	if (curr->next->type != WORD)
		return (syntax_err(curr->next->value));
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*curr;

	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
		return (syntax_err("|"));
	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE && check_pipe(curr))
			return (1);
		if (is_redirection(curr->type) && check_redir(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}
