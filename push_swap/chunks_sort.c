/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 16:38:23 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:03:06 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunk_size_for(int n)
{
	if (n <= 100)
		return (20);
	return (n / 11);
}

static void	push_chunk(t_stack *a, t_stack *b, int start, int end)
{
	int	total;
	int	pushed;

	total = end - start + 1;
	pushed = 0;
	while (pushed < total)
	{
		if (a->top->index >= start && a->top->index <= end)
		{
			pb(a, b);
			pushed++;
			if (b->top->index < (start + end) / 2)
				rb(b);
		}
		else
			ra(a);
	}
}

static void	find_max_and_pos(t_stack *b, int *max, int *pos)
{
	t_node	*cur;
	int		i;

	cur = b->top;
	*max = cur->index;
	*pos = 0;
	i = 0;
	while (cur)
	{
		if (cur->index > *max)
		{
			*max = cur->index;
			*pos = i;
		}
		cur = cur->next;
		i++;
	}
}

static void	push_back_all(t_stack *a, t_stack *b)
{
	int	max;
	int	pos;

	while (b->size)
	{
		find_max_and_pos(b, &max, &pos);
		if (pos <= b->size / 2)
			while (b->top->index != max)
				rb(b);
		else
			while (b->top->index != max)
				rrb(b);
		pa(a, b);
	}
}

void	chunk_sort(t_stack *a, t_stack *b)
{
	int	n;
	int	chunk;
	int	start;
	int	end;

	n = a->size;
	chunk = chunk_size_for(n);
	start = 0;
	end = chunk - 1;
	while (start < n)
	{
		if (end >= n)
			end = n - 1;
		push_chunk(a, b, start, end);
		start = end + 1;
		end = start + chunk - 1;
	}
	push_back_all(a, b);
}
