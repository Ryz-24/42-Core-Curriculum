/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:12:42 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/05/24 13:12:52 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv)
{
	int	status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
		exit(g_exit_status);
	if (!is_numeric(argv[1]))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (argv[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	status = ft_atoi(argv[1]);
	exit(status % 256);
}
