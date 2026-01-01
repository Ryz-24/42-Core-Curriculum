/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 16:53:32 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/01 17:02:50 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	fill_array(t_stack *a, int *arr)
{
	t_node	*cur;
	int		i;

	cur = a->top;
	i = 0;
	while (cur)
	{
		arr[i] = cur->value;
		cur = cur->next;
		i++;
	}
}

static void	sort_array(int *arr, int n)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	index_stack(t_stack *a)
{
	int		i;
	int		*arr;
	t_node	*cur;

	arr = malloc(sizeof(int) * a->size);
	if (!arr)
		error_exit();
	fill_array(a, arr);
	sort_array(arr, a->size);
	cur = a->top;
	while (cur)
	{
		i = 0;
		while (i < a->size)
		{
			if (arr[i] == cur->value)
			{
				cur->index = i;
				break ;
			}
			i++;
		}
		cur = cur->next;
	}
	free(arr);
}
