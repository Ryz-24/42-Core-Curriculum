/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:25:21 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/27 15:41:42 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

static void	send_char(pid_t pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_ack = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_ack)
			pause();
		bit--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
	{
		ft_printf("Usage: %s <pid> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, ack_handler);
	i = 0;
	while (argv[2][i])
		send_char(pid, (unsigned char)argv[2][i++]);
	send_char(pid, '\0');
	return (0);
}
