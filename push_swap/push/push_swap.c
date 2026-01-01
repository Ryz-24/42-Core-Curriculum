/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 16:34:07 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 16:37:47 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;

	init_stack(&a);
	init_stack(&b);
	if (ac < 2)
		return (0);
	parse_args(&a, ac, av);
	if (is_sorted(&a))
	{
		free_stack(&a);
		return (0);
	}
	index_stack(&a);
	if (a.size == 2)
		sort_2(&a);
	else if (a.size == 3)
		sort_3(&a);
	else if (a.size == 4)
		sort_4(&a, &b);
	else if (a.size == 5)
		sort_5(&a, &b);
	else
		chunk_sort(&a, &b);
	free_stack(&a);
	free_stack(&b);
}
