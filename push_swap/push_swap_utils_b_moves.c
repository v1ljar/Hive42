/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_b_moves.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:37:28 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/08 12:11:33 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb(t_stack *stack_b)
{
	int	temp;

	if (stack_b->size > 1)
	{
		temp = stack_b->arr[0];
		stack_b->arr[0] = stack_b->arr[1];
		stack_b->arr[1] = temp;
		ft_printf("sb\n");
	}
}

void	rb(t_stack *stack_b)
{
	int	temp;
	int	i;

	if (stack_b->size > 0)
	{
		temp = stack_b->arr[0];
		i = 0;
		while (i < stack_b->size - 1)
		{
			stack_b->arr[i] = stack_b->arr[i + 1];
			i++;
		}
		stack_b->arr[stack_b->size - 1] = temp;
		ft_printf("rb\n");
	}
}

void	rrb(t_stack *stack_b)
{
	int	temp;
	int	i;

	if (stack_b->size > 0)
	{
		temp = stack_b->arr[stack_b->size - 1];
		i = stack_b->size - 1;
		while (i > 0)
		{
			stack_b->arr[i] = stack_b->arr[i - 1];
			i--;
		}
		stack_b->arr[0] = temp;
		ft_printf("rrb\n");
	}
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	int	i;

	if (stack_a->size > 0)
	{
		i = stack_b->size;
		while (i > 0)
		{
			stack_b->arr[i] = stack_b->arr[i - 1];
			i--;
		}
		stack_b->arr[0] = stack_a->arr[0];
		stack_b->size++;
		i = 0;
		while (i < stack_a->size - 1)
		{
			stack_a->arr[i] = stack_a->arr[i + 1];
			i++;
		}
		stack_a->size--;
		ft_printf("pb\n");
	}
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	int	temp;
	int	i;

	if (stack_a->size != 0 && stack_b->size != 0)
	{
		temp = stack_a->arr[stack_a->size - 1];
		i = stack_a->size - 1;
		while (i > 0)
		{
			stack_a->arr[i] = stack_a->arr[i - 1];
			i--;
		}
		stack_a->arr[0] = temp;
		temp = stack_b->arr[stack_b->size - 1];
		i = stack_b->size - 1;
		while (i > 0)
		{
			stack_b->arr[i] = stack_b->arr[i - 1];
			i--;
		}
		stack_b->arr[0] = temp;
		ft_printf("rrr\n");
	}
}
