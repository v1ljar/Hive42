/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_sort_make_moves.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:06:06 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/07 16:33:57 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_values(t_stack *st_a, t_stack *st_b, t_cost *res, t_values *values);
void	ft_moves_before_pb(t_stack *st_a, t_stack *st_b, t_values *values);

void	ft_make_moves(t_cost *result, t_stack *stack_a, t_stack *stack_b)
{
	t_values	values;

	values.ra_v = 0;
	values.rb_v = 0;
	values.rra_v = 0;
	values.rrb_v = 0;
	if (result->a_cost > 0 || result->b_cost > 0)
		ft_values(stack_a, stack_b, result, &values);
	if (values.ra_v > 0 || values.rb_v > 0 || values.rra_v > 0
		|| values.rrb_v > 0)
		ft_moves_before_pb(stack_a, stack_b, &values);
	pb(stack_a, stack_b);
}

void	ft_values(t_stack *st_a, t_stack *st_b, t_cost *res, t_values *values)
{
	if (res->a_cost <= st_a->size / 2)
		values->ra_v = res->a_cost;
	else
		values->rra_v = st_a->size - res->a_cost;
	if (res->b_cost <= st_b->size / 2)
		values->rb_v = res->b_cost;
	else
		values->rrb_v = st_b->size - res->b_cost;
}

void	ft_moves_before_pb(t_stack *st_a, t_stack *st_b, t_values *values)
{
	if (values->ra_v > 0 || values->rb_v > 0
		|| values->rra_v > 0 || values->rrb_v > 0)
	{
		while (values->ra_v > 0 && values->rb_v > 0)
		{
			rr(st_a, st_b);
			values->ra_v--;
			values->rb_v--;
		}
		while (values->rra_v > 0 && values->rrb_v > 0)
		{
			rrr(st_a, st_b);
			values->rra_v--;
			values->rrb_v--;
		}
		while (values->ra_v-- > 0)
			ra(st_a);
		while (values->rb_v-- > 0)
			rb(st_b);
		while (values->rra_v-- > 0)
			rra(st_a);
		while (values->rrb_v-- > 0)
			rrb(st_b);
	}
}
