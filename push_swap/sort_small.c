/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:03:54 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:07:52 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_2(t_stack *a)
{
	if (!a || a->size < 2)
		return ;
	if (a->top->value > a->top->next->value)
		sa(a);
}

void	sort_3(t_stack *a)
{
	int	x;
	int	y;
	int	z;

	x = a->top->value;
	y = a->top->next->value;
	z = a->top->next->next->value;
	if (x > y && y < z && x < z)
		sa(a);
	else if (x > y && y > z)
	{
		sa(a);
		rra(a);
	}
	else if (x > y && y < z && x > z)
		ra(a);
	else if (x < y && y > z && x < z)
	{
		sa(a);
		ra(a);
	}
	else if (x < y && y > z && x > z)
		rra(a);
}

void	sort_4(t_stack *a, t_stack *b)
{
	int	pos;

	pos = find_pos_by_index(a, 0);
	rotate_to_pos(a, pos);
	pb(a, b);
	sort_3(a);
	pa(a, b);
}

void	sort_5(t_stack *a, t_stack *b)
{
	int	pos;

	pos = find_pos_by_index(a, 0);
	rotate_to_pos(a, pos);
	pb(a, b);
	pos = find_pos_by_index(a, 1);
	rotate_to_pos(a, pos);
	pb(a, b);
	sort_3(a);
	if (b->top->index < b->top->next->index)
		sb(b);
	pa(a, b);
	pa(a, b);
}
