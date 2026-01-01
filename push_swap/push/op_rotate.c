/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:19:55 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:23:11 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack *stack)
{
	t_node	*top_node;

	if (stack->size < 2)
		return ;
	top_node = stack->top;
	stack->top = top_node->next;
	stack->top->prev = NULL;
	top_node->next = NULL;
	top_node->prev = stack->bottom;
	stack->bottom->next = top_node;
	stack->bottom = top_node;
}

void	ra(t_stack *a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}
