/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:47:02 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:53:59 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	parse_value(t_stack *a, char *str, char **parts)
{
	long	v;

	if (!ft_isnumber(str))
	{
		free_split(parts);
		free_stack(a);
		error_exit();
	}
	v = ft_atoi(str);
	if (v < INT_MIN || v > INT_MAX)
	{
		free_split(parts);
		free_stack(a);
		error_exit();
	}
	if (check_duplicate(a, (int)v))
	{
		free_split(parts);
		free_stack(a);
		error_exit();
	}
	push_bottom(a, new_node((int)v));
}


void	parse_args(t_stack *a, int ac, char **av)
{
	int		i;
	int		j;
	char	**parts;

	i = 1;
	while (i < ac)
	{
		parts = ft_split(av[i], ' ');
		if (!parts)
		{
			free_stack(a);
			error_exit();
		}
		j = 0;
		while (parts[j])
		{
			parse_value(a, parts[j], parts);
			j++;
		}
		free_split(parts);
		i++;
	}
}
