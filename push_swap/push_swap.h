#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "libft/libft.h"


typedef struct s_node
{
	int		value;
	int		index;
	struct s_node *next;
	struct s_node *prev;
} t_node;

typedef struct s_stack
{
	t_node *top;
	t_node *bottom;
	int	size;
} t_stack;


/* parsing */
void parse_args(t_stack *a, int ac, char **av);
void error_exit(void);


/* stack init & utils */
void init_stack(t_stack *s);
void push_top(t_stack *s, t_node *n);
void push_bottom(t_stack *s, t_node *n);
int is_sorted(t_stack *a);


t_node *new_node(int value);


/* ops */
void sa(t_stack *a);
void sb(t_stack *b);
void ss(t_stack *a, t_stack *b);
void pa(t_stack *a, t_stack *b);
void pb(t_stack *a, t_stack *b);
void ra(t_stack *a);
void rb(t_stack *b);
void rr(t_stack *a, t_stack *b);
void rra(t_stack *a);
void rrb(t_stack *b);
void rrr(t_stack *a, t_stack *b);


/* algorithm */
void index_stack(t_stack *a);
void chunk_sort(t_stack *a, t_stack *b);
void	rotate_to_pos(t_stack *a, int pos);
int	find_pos_by_index(t_stack *a, int index);

/* small sorts */
void sort_2(t_stack *a);
void sort_3(t_stack *a);
void sort_4(t_stack *a, t_stack *b);
void sort_5(t_stack *a, t_stack *b);


/* utils */
int ft_isnumber(const char *s);
void free_split(char **arr);
void	free_stack(t_stack *s);
int	check_duplicate(t_stack *a, int value);

#endif


