/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_check_stack.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:18:51 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/07 17:32:04 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_check_stack_completed(t_stack *stack_a)
{
	int	valid;

	valid = ft_check_stack_order(stack_a);
	if (valid == -1 || valid > 0)
		ft_sort_stack(stack_a);
	free(stack_a->arr);
	
}

int	ft_check_stack_order(t_stack *stack_a)
{
	int	i;
	int	smallest_index;
	int	current;
	int	next;

	smallest_index = 0;
	i = 1;
	while (i < stack_a->size)
	{
		if (stack_a->arr[i] < stack_a->arr[smallest_index])
			smallest_index = i;
		i++;
	}
	i = 0;
	while (stack_a->size > 0 && i < stack_a->size - 1)
	{
		current = stack_a->arr[(smallest_index + i) % stack_a->size];
		next = stack_a->arr[(smallest_index + i + 1) % stack_a->size];
		if (current > next)
			return (-1);
		i++;
	}
	return (smallest_index);
}

void	ft_stack_b_final_check(t_stack *stack_b)
{
	int	seq_b;

	seq_b = ft_check_stack_b_order(stack_b);
	if (seq_b > 0)
	{
		if (seq_b > stack_b->size / 2)
		{
			seq_b = stack_b->size - seq_b;
			while (seq_b-- > 0)
				rrb(stack_b);
		}
		else
		{
			while (seq_b-- > 0)
				rb(stack_b);
		}
	}
}

int	ft_check_stack_b_order(t_stack *stack_b)
{
	int	i;
	int	biggest_index;
	int	current;
	int	next;

	biggest_index = 0;
	i = 1;
	while (i < stack_b->size)
	{
		if (stack_b->arr[i] > stack_b->arr[biggest_index])
			biggest_index = i;
		i++;
	}
	i = 0;
	while (i < stack_b->size - 1)
	{
		current = stack_b->arr[(biggest_index + i) % stack_b->size];
		next = stack_b->arr[(biggest_index + i + 1) % stack_b->size];
		if (current < next)
			return (-1);
		i++;
	}
	return (biggest_index);
}

void	ft_free_and_exit(char **buf, t_stack *stack_a)
{
	free(stack_a->arr);
	ft_free_split(buf);
	exit(write(2, "Error\n", 6));
}
