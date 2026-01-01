/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:08:56 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:15:02 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack *a, t_stack *b)
{
	t_node	*n;

	if (b->size < 1)
		return ;
	n = b->top;
	b->top = n->next;
	if (b->top)
		b->top->prev = NULL;
	else
		b->bottom = NULL;
	b->size--;
	n->next = a->top;
	n->prev = NULL;
	if (a->top)
		a->top->prev = n;
	else
		a->bottom = n;
	a->top = n;
	a->size++;
	write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	t_node	*n;

	if (a->size < 1)
		return ;
	n = a->top;
	a->top = n->next;
	if (a->top)
		a->top->prev = NULL;
	else
		a->bottom = NULL;
	a->size--;
	n->next = b->top;
	n->prev = NULL;
	if (b->top)
		b->top->prev = n;
	else
		b->bottom = n;
	b->top = n;
	b->size++;
	write(1, "pb\n", 3);
}
