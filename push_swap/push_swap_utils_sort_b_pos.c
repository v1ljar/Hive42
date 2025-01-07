/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_sort_b_pos.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:13:06 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/07 15:57:27 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_stack_b_greatest(t_stack *stack_b);

int	ft_stack_b_pos(t_stack *stack_b, int value)
{
	int	i;

	i = 0;
	if (stack_b->size > 0 && (value > stack_b->arr[i]
			&& value < stack_b->arr[stack_b->size - 1]))
		return (i);
	while (i < stack_b->size - 1)
	{
		if (value < stack_b->arr[i] && value > stack_b->arr[i + 1])
			return (i + 1);
		i++;
	}
	if (i == stack_b->size - 1)
		i = ft_stack_b_greatest(stack_b);
	return (i);
}

static int	ft_stack_b_greatest(t_stack *stack_b)
{
	int	pos_greatest;
	int	i;

	pos_greatest = 0;
	i = 1;
	while (i < stack_b->size)
	{
		if (stack_b->arr[i] > stack_b->arr[pos_greatest])
			pos_greatest = i;
		i++;
	}
	return (pos_greatest);
}
