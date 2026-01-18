/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:50:23 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:53:11 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_pos_by_index(t_stack *a, int index)
{
	t_node	*cur;
	int		pos;

	cur = a->top;
	pos = 0;
	while (cur)
	{
		if (cur->index == index)
			return (pos);
		cur = cur->next;
		pos++;
	}
	return (-1);
}

void	rotate_to_pos(t_stack *a, int pos)
{
	if (pos <= a->size / 2)
		while (pos-- > 0)
			ra(a);
	else
		while (pos++ < a->size)
			rra(a);
}
