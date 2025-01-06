/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_a_moves.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:32:16 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/06 13:32:16 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void  sa(t_stack *stack_a)
{
  int temp;

  temp = stack_a->arr[0];
  stack_a->arr[0] = stack_a->arr[1];
  stack_a->arr[1] = temp;
  ft_printf("sa\n");
}

void  ra(t_stack *stack_a)
{
  int temp;
  int i;

  temp = stack_a->arr[0];
  i = 0;
  while (i < stack_a->size - 1)
  {
    stack_a->arr[i] = stack_a->arr[i + 1];
    i++;
  }
  stack_a->arr[stack_a->size - 1] = temp;
  ft_printf("ra\n");
}

void  rra(t_stack *stack_a)
{
  int temp;
  int i;

  temp = stack_a->arr[stack_a->size - 1];
  i = stack_a->size - 1;
  while (i > 0)
  {
    stack_a->arr[i] = stack_a->arr[i - 1];
    i--; 
  }
  stack_a->arr[0] = temp;
  ft_printf("rra\n");
}

void  pa(t_stack *stack_a, t_stack *stack_b)
{
  int i;

  i = stack_a->size;
  while (i > 0)
  {
    stack_a->arr[i] = stack_a->arr[i - 1];
    i--;
  }
  stack_a->arr[0] = stack_b->arr[0];
  stack_a->size++;
  i = 0;
  while (i < stack_b->size - 1)
  {
    stack_b->arr[i] = stack_b->arr[i + 1];
    i++;
  }
  stack_b->size--;
  ft_printf("pa\n");
}

void  rr(t_stack *stack_a, t_stack *stack_b)
{
  int temp;
  int i;

  temp = stack_a->arr[0];
  i = 0;
  while (i < stack_a->size - 1)
  {
    stack_a->arr[i] = stack_a->arr[i + 1];
    i++;
  }
  stack_a->arr[stack_a->size - 1] = temp;
  temp = stack_b->arr[0];
  i = 0;
  while (i < stack_b->size - 1)
  {
    stack_b->arr[i] = stack_b->arr[i + 1];
    i++;
  }
  stack_b->arr[stack_b->size - 1] = temp;
  ft_printf("rr\n");
}