/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:35:59 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:42:19 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack(t_stack *s)
{
	s->top = NULL;
	s->bottom = NULL;
	s->size = 0;
}

t_node	*new_node(int value)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		error_exit();
	n->value = value;
	n->index = -1;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

void	push_top(t_stack *s, t_node *new)
{
	if (!new)
		return ;
	new->next = s->top;
	new->prev = NULL;
	if (s->top)
		s->top->prev = new;
	else
		s->bottom = new;
	s->top = new;
	s->size++;
}

void	push_bottom(t_stack *s, t_node *new)
{
	if (!new)
		return ;
	new->next = NULL;
	new->prev = s->bottom;
	if (s->bottom)
		s->bottom->next = new;
	else
		s->top = new;
	s->bottom = new;
	s->size++;
}
