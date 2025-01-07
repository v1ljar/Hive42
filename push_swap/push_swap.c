/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:46:06 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/07 16:29:39 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_sort_two(t_stack *stack_a);
static void	ft_sort_three(t_stack *stack_a);
static void	ft_sort_rest(t_stack *stack_a);

int	main(int argc, char **argv)
{
	size_t	total_args;
	t_stack	stack_a;

	if (argc < 2)
		return (0);
	total_args = ft_validate_argv(argc, argv);
	stack_a.arr = ft_calloc(sizeof(int), total_args);
	if (!stack_a.arr)
		exit(write(2, "Error\n", 6));
	stack_a.size = 0;
	ft_fill_stack_a(&stack_a, argc, argv);
	ft_check_stack_completed(&stack_a);
	ft_sort_stack(&stack_a);
	ft_check_stack_completed(&stack_a);
	free(stack_a.arr);
	return (0);
}

void	ft_sort_stack(t_stack *stack_a)
{
	int	seq;

	seq = ft_check_stack_order(stack_a);
	if (seq == -1)
	{
		if (stack_a->size == 2)
			ft_sort_two(stack_a);
		else if (stack_a->size == 3)
			ft_sort_three(stack_a);
		else
			ft_sort_rest(stack_a);
	}
	if (seq > stack_a->size / 2)
	{
		seq = stack_a->size - seq;
		while (seq > 0)
		{
			rra(stack_a);
			seq--;
		}
	}
	while (seq-- > 0)
		ra(stack_a);
}

static void	ft_sort_two(t_stack *stack_a)
{
	if (stack_a->arr[0] > stack_a->arr[1])
		sa(stack_a);
}

static void	ft_sort_three(t_stack *stack_a)
{
	int	a;
	int	b;
	int	c;

	a = stack_a->arr[0];
	b = stack_a->arr[1];
	c = stack_a->arr[2];
	if (a > b && b < c && a < c)
		sa(stack_a);
	else if (a > b && b > c)
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if (a < b && b > c && a < c)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (a < b && b > c && a > c)
		rra(stack_a);
	else if (a > b && b < c)
		ra(stack_a);
}

static void	ft_sort_rest(t_stack *stack_a)
{
	t_stack	stack_b;
	t_array	biggest;

	stack_b.arr = ft_calloc(sizeof(int), (size_t)(stack_a->size - 3));
	if (!stack_b.arr)
	{
		free(stack_a->arr);
		exit(write(2, "Error\n", 6));
	}
	stack_b.size = 0;
	ft_find_largest_values(stack_a, &biggest);
	while (stack_a->size > 3)
	{
		if (stack_a->arr[0] == biggest.largest || stack_a->arr[0] == biggest.sec
			|| stack_a->arr[0] == biggest.third)
			ra(stack_a);
		else
			ft_calculate_cost(stack_a, &stack_b, &biggest);
	}
	ft_stack_b_final_check(&stack_b);
	ft_sort_three(stack_a);
	while (stack_b.size > 0)
		pa(stack_a, &stack_b);
	free(stack_b.arr);
}
