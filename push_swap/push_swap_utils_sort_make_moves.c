/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_sort_make_moves.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:06:06 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/06 13:06:06 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void  ft_initialize_values(t_stack *stack_a, t_stack *stack_b, t_cost *result, t_values *values);
static void  ft_moves_before_pb(t_stack *stack_a, t_stack *stack_b, t_values *values);

void  ft_make_moves(t_cost *result, t_stack *stack_a, t_stack *stack_b)
{
  t_values  values;

  values.ra_v = 0;
  values.rb_v = 0;
  values.rra_v = 0;
  values.rrb_v = 0;
  if (result->a_cost > 0 || result->b_cost > 0)
    ft_initialize_values(stack_a, stack_b, result, &values);
  if (values.ra_v > 0 || values.rb_v > 0 || values.rra_v > 0 || values.rrb_v > 0)
    ft_moves_before_pb(stack_a, stack_b, &values);
  pb(stack_a, stack_b);
}

static void  ft_initialize_values(t_stack *stack_a, t_stack *stack_b, t_cost *result, t_values *values)
{
  if (result->a_cost <= stack_a->size / 2)
    values->ra_v = result->a_cost;
  else
    values->rra_v = stack_a->size - result->a_cost;
  if (result->b_cost <= stack_b->size / 2)
    values->rb_v = result->b_cost;
  else
    values->rrb_v = stack_b->size - result->b_cost;
}

static void  ft_moves_before_pb(t_stack *stack_a, t_stack *stack_b, t_values *values)
{
  if (values->ra_v > 0 || values->rb_v > 0 || values->rra_v > 0 || values->rrb_v > 0)
  {
    while (values->ra_v > 0 && values->rb_v > 0)
    {
      rr(stack_a, stack_b);
      values->ra_v--;
      values->rb_v--;
    }
    while (values->rra_v > 0 && values->rrb_v > 0)
    {
      rrr(stack_a, stack_b);
      values->rra_v--;
      values->rrb_v--;
    }
    while (values->ra_v-- > 0)
      ra(stack_a);
    while (values->rb_v-- > 0)
      rb(stack_b);
    while (values->rra_v-- > 0)
      rra(stack_a);
    while (values->rrb_v-- > 0)
      rrb(stack_b);
  }
}