/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:52:40 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/16 12:49:26 by rzaatreh         ###   ########.fr       */
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
	return (quote != 0);
}
