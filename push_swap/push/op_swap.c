/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:15:30 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:18:40 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack)
{
	t_node	*x;
	t_node	*y;

	if (stack->size < 2)
		return ;
	x = stack->top;
	y = x->next;
	x->next = y->next;
	if (y->next)
		y->next->prev = x;
	y->prev = NULL;
	y->next = x;
	x->prev = y;
	stack->top = y;
	if (stack->size == 2)
		stack->bottom = x;
}

void	sa(t_stack *a)
{
	swap(a);
	write(1, "sa\n", 3);
}

void	sb(t_stack *b)
{
	swap(b);
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}
