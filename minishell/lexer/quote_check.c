/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:52:40 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:15:57 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (quote != 0)
	{
		ft_putstr_fd("minishell: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
