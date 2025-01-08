/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:24:06 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/07 17:36:09 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_init_m_cost(t_stack *st_a, t_stack *st_b, t_cost *m, int i);
static void	ft_save_least_moves(t_cost *result, t_cost *moves);
static void	ft_initialize_cost_structs(t_cost *moves, t_cost *result);

void	ft_find_largest_values(t_stack *stack_a, t_array *biggest)
{
	int	i;

	biggest->largest = INT_MIN;
	biggest->sec = INT_MIN;
	biggest->third = INT_MIN;
	i = 0;
	while (i < stack_a->size)
	{
		if (stack_a->arr[i] > biggest->largest)
		{
			biggest->third = biggest->sec;
			biggest->sec = biggest->largest;
			biggest->largest = stack_a->arr[i];
		}
		else if (stack_a->arr[i] > biggest->sec)
		{
			biggest->third = biggest->sec;
			biggest->sec = stack_a->arr[i];
		}
		else if (stack_a->arr[i] > biggest->third)
			biggest->third = stack_a->arr[i];
		i++;
	}
}

static void	ft_initialize_cost_structs(t_cost *moves, t_cost *result)
{
	moves->a_cost = 0;
	moves->b_cost = 0;
	moves->total = 2147483647;
	result->a_cost = 0;
	result->b_cost = 0;
	result->total = 2147483647;
}

void	ft_calculate_cost(t_stack *st_a, t_stack *st_b, t_array *big)
{
	t_cost	moves;
	t_cost	result;
	int		i;

	ft_initialize_cost_structs(&moves, &result);
	i = 0;
	while (i < st_a->size)
	{
		if (st_a->arr[i] == big->largest || st_a->arr[i] == big->sec
			|| st_a->arr[i] == big->third)
			i++;
		else
		{
			ft_init_m_cost(st_a, st_b, &moves, i);
			moves.a_cost = i;
			if (moves.total <= result.total)
				ft_save_least_moves(&result, &moves);
			i++;
		}
	}
	ft_make_moves(&result, st_a, st_b);
}

static void	ft_save_least_moves(t_cost *result, t_cost *moves)
{
	result->a_cost = moves->a_cost;
	result->b_cost = moves->b_cost;
	result->total = moves->total;
}

static void	ft_init_m_cost(t_stack *st_a, t_stack *st_b, t_cost *m, int i)
{
	int	b_pos;

	b_pos = ft_stack_b_pos(st_b, st_a->arr[i]);
	if (i <= st_a->size / 2)
		m->a_cost = i;
	else
		m->a_cost = st_a->size - i;
	if (b_pos <= st_b->size / 2)
	{
		m->b_cost = b_pos;
		m->total = m->a_cost + m->b_cost;
	}
	else
	{
		m->b_cost = b_pos;
		m->total = m->a_cost + (st_b->size - b_pos);
	}
}
