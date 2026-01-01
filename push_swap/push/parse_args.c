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

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	check_duplicate(t_stack *a, int value)
{
	t_node	*nod;

	nod = a->top;
	while (nod)
	{
		if (nod->value == value)
			return (1);
		nod = nod->next;
	}
	return (0);
}

void	free_stack(t_stack *s)
{
	t_node	*tmp;

	while (s->top)
	{
		tmp = s->top;
		s->top = s->top->next;
		free(tmp);
	}
	s->bottom = NULL;
	s->size = 0;
}

void	parse_args(t_stack *a, int ac, char **av)
{
	int			i;
	int			j;
	char		**parts;
	long		v;

	i = 1;
	while (i < ac)
	{
		parts = ft_split(av[i], ' ');
		if (!parts)
			error_exit();
		j = 0;
		while (parts[j])
		{
			if (!ft_isnumber(parts[j]))
				(free_split(parts), free_stack(a), error_exit());
			v = ft_atoi(parts[j]);
			if (v < INT_MIN || v > INT_MAX)
				(free_split(parts), free_stack(a), error_exit());
			if (check_duplicate(a, (int)v))
				(free_split(parts), free_stack(a), error_exit());
			push_bottom(a, new_node((int)v));
			j++;
		}
		free_split(parts);
		i++;
	}
}
