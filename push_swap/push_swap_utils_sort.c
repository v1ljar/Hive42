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

void		ft_initialize_biggest(t_array *biggest)
{
	int	i;

	i = 0;
	while (i < biggest->amount)
	{
		biggest->largest[i] = -2147483648;
		i++;
	}
}

void	ft_find_largest_values(t_stack *stack_a, t_array *biggest)
{
	int	i;
	int	j;
	int	k;
	int	len;

	if (stack_a->size == 4 || stack_a->size == 5)
		len = 3;
	else
		len = 5;
	biggest->amount = len;
	biggest->largest = malloc(sizeof(int) * len);
	if (!biggest->largest)
	{
		free(stack_a->arr);
		exit(write(2, "Error\n", 6));
	}
	ft_initialize_biggest(biggest);
	/*i = 0;
	while (i < biggest->amount)
	{
		ft_printf("%d | %d\n", biggest->amount, i);
		ft_printf("%d\n", biggest->largest[i]);
		i++;
	}*/
	i = 0;
	while (i < stack_a->size)
	{
		j = len - 1;
		while (j >= 0)
		{
			if (stack_a->arr[i] > biggest->largest[j])
			{
				k = 0;
				while (k < j)
				{
					biggest->largest[k] =  biggest->largest[k + 1];
					k++;
				}
				biggest->largest[j] = stack_a->arr[i];
				break;
			}
			j--;
		}
		i++;
	}
	/*while (i < stack_a->size)
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
	}*/
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
int	ft_comp_biggest(int x, t_array *big)
{
	int	i;

	i = 0;
	while (i < big->amount)
	{
		if (x == big->largest[i])
			return (1);
		i++;
	}
	return (0);
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
		if (ft_comp_biggest(st_a->arr[i], big) == 1)
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

/*void	ft_calculate_cost(t_stack *st_a, t_stack *st_b, t_array *big)
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
}*/

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
