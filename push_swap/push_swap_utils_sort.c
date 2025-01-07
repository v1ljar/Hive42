/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:23:06 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/06 12:23:06 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void  ft_initialize_moves_cost(t_stack *stack_a, t_stack *stack_b, t_cost *moves, int i);
static void  ft_save_least_moves(t_cost *result, t_cost *moves);

void  ft_find_largest_values(t_stack *stack_a, t_array *biggest)
{
  int i;

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

void ft_calculate_cost(t_stack *stack_a, t_stack *stack_b, t_array *biggest)
{
  t_cost  moves;
  t_cost  result;
  int     i;

  moves.a_cost = 0;
  moves.b_cost = 0;
  moves.total = 2147483647;
  result.a_cost = 0;
  result.b_cost = 0;
  result.total = 2147483647;
  i = 0;
  while (i < stack_a->size)
  {
    if (stack_a->arr[i] == biggest->largest || stack_a->arr[i] == biggest->sec || stack_a->arr[i] == biggest->third)
      i++;
    else
    {
      ft_initialize_moves_cost(stack_a, stack_b, &moves, i);
      moves.a_cost = i;
      if (moves.total <= result.total)
        ft_save_least_moves(&result, &moves);
      i++;
    }
  }
  ft_make_moves(&result, stack_a, stack_b);
}
static void  ft_save_least_moves(t_cost *result, t_cost *moves)
{
  result->a_cost = moves->a_cost;
  result->b_cost = moves->b_cost;
  result->total = moves->total;
}

static void  ft_initialize_moves_cost(t_stack *stack_a, t_stack *stack_b, t_cost *moves, int i)
{
  if (i <= stack_a->size / 2)
    moves->a_cost = i;
  else
    moves->a_cost = stack_a->size - i;
  if (ft_stack_b_pos(stack_b, stack_a->arr[i]) <= stack_b->size / 2)
  {
    moves->b_cost = ft_stack_b_pos(stack_b, stack_a->arr[i]);
    moves->total = moves->a_cost + moves->b_cost;        
  }
  else
  {
    moves->b_cost = ft_stack_b_pos(stack_b, stack_a->arr[i]);
    moves->total = moves->a_cost + (stack_b->size - ft_stack_b_pos(stack_b, stack_a->arr[i]));
  }
}

