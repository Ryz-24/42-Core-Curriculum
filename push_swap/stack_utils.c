#include "push_swap.h"

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

int	is_sorted(t_stack *a)
{
	t_node	*nod;

	nod = a->top;
	if (!a || a->size < 2)
		return (1);
	while (nod && nod->next)
	{
		if (nod->value > nod->next->value)
			return (0);
		nod = nod->next;
	}
	return (1);
}
