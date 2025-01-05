/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:46:06 by vuljas            #+#    #+#             */
/*   Updated: 2024/12/23 15:56:51 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void  check_stack_completed(t_stack *stack_a);
int   check_stack_order(t_stack *stack_a);
void  sort_stack(t_stack *stack_a);
void  sort_two(t_stack *stack_a);
void  sort_three(t_stack *stack_a);
void  sort_rest(t_stack *stack_a);
void  sa(t_stack *stack_a);
void  sb(t_stack *stack_b);
void  ra(t_stack *stack_a);
void  rb(t_stack *stack_a);
void  rra(t_stack *stack_a);
void  rrb(t_stack *stack_b);
void  pb(t_stack *stack_a, t_stack *stack_b);
void  pa(t_stack *stack_a, t_stack *stack_b);
void  rr(t_stack *stack_a, t_stack *stack_b);
void  rrr(t_stack *stack_a, t_stack *stack_b);
void  find_largest_values(t_stack *stack_a, t_array *biggest);
void  align_stack_b(t_stack *stack_b, int value);
void  stack_b_final_check(t_stack *stack_b);
int   check_stack_b_order(t_stack *stack_b);
int   ft_stack_b_greatest(t_stack *stack_b);
int   ft_stack_b_pos(t_stack *stack_b, int value);
void  calculate_cost(t_stack *stack_a,t_stack *stack_b, t_array *biggest);
void  ft_make_moves(t_cost *result, t_stack *stack_a, t_stack *stack_b);
void  ft_initialize_moves_cost(t_stack *stack_a, t_stack *stack_b, t_cost *moves, int i);
void  ft_save_least_moves(t_cost *result, t_cost *moves);
void  ft_initialize_values(t_stack *stack_a, t_stack *stack_b, t_cost *result, t_values *values);
void  ft_moves_before_pb(t_stack *stack_a, t_stack *stack_b, t_values *values);

int main(int argc, char **argv)
{
	size_t		total_args;
	t_stack	stack_a;

	if (argc < 2)
		return(0);
	total_args = ft_validate_argv(argc, argv);
	stack_a.arr = ft_calloc(sizeof(int), total_args);
	if (!stack_a.arr)
		return (write(1, "Error\n", 6));
	stack_a.size = 0;
	fill_stack_a(&stack_a, argc, argv);
  check_stack_completed(&stack_a);
  sort_stack(&stack_a);
  check_stack_completed(&stack_a);
	free(stack_a.arr);  
	return (0);
}

void check_stack_completed(t_stack *stack_a)
{
  int i;
  int valid;

  i = 1;
  valid = check_stack_order(stack_a);
  if (valid == -1)
    sort_stack(stack_a);
  ft_printf("Sorted!\n");
  free(stack_a->arr);
  exit(0);
}

int check_stack_order(t_stack *stack_a)
{
  int i;
  int  smallest_index;
  int current;
  int next;

  smallest_index = 0;
  i = 1;
  while (i < stack_a->size)
  {
    if (stack_a->arr[i] < stack_a->arr[smallest_index])
      smallest_index = i;
    i++;
  }
  i = 0;
  while (i < stack_a->size - 1)
  {
    current = stack_a->arr[(smallest_index + i) % stack_a->size];
    next = stack_a->arr[(smallest_index + i + 1) % stack_a->size];
    if (current > next)
      return (-1);
    i++;
  }
  return (smallest_index);
}

void  sort_stack(t_stack *stack_a)
{
  int seq;

  seq = check_stack_order(stack_a);
  if (seq == -1)
  {
    if (stack_a->size == 2)
      sort_two(stack_a);
    else if (stack_a->size == 3)
      sort_three(stack_a);
    else
      sort_rest(stack_a);
  }
  else if (seq != 0)
  {
    if (seq > stack_a->size / 2)
    {
      while (stack_a->size - seq--)
        rra(stack_a);
    }
    while (seq--)
      ra(stack_a);
  }
}

void  sort_two(t_stack *stack_a)
{
  if (stack_a->arr[0] > stack_a->arr[1])
    sa(stack_a);
}

void  sort_three(t_stack *stack_a)
{
  int a;
  int b;
  int c;

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

void  sort_rest(t_stack *stack_a)
{
  t_stack stack_b;
  t_array  biggest;

  stack_b.arr = ft_calloc(sizeof(int), (size_t)(stack_a->size - 3));
  if (!stack_b.arr)
  {
    free(stack_a->arr);
    exit(write(1, "Error\n", 6));
  }
  stack_b.size = 0;
  find_largest_values(stack_a, &biggest);
  while (stack_a->size > 3)
  {
    if (stack_a->arr[0] == biggest.largest || stack_a->arr[0] == biggest.sec
    || stack_a->arr[0] == biggest.third)
      ra(stack_a);
    else
      calculate_cost(stack_a, &stack_b, &biggest);
  }
  stack_b_final_check(&stack_b);
  sort_three(stack_a);
  while (stack_b.size > 0)
    pa(stack_a, &stack_b);
  free(stack_b.arr);
}

void calculate_cost(t_stack *stack_a, t_stack *stack_b, t_array *biggest)
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
        ft_save_least_moves(&result, & moves);
      i++;
    }
  }
  ft_make_moves(&result, stack_a, stack_b);
}
void  ft_save_least_moves(t_cost *result, t_cost *moves)
{
  result->a_cost = moves->a_cost;
  result->b_cost = moves->b_cost;
  result->total = moves->total;
}

void  ft_initialize_moves_cost(t_stack *stack_a, t_stack *stack_b, t_cost *moves, int i)
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

void  find_largest_values(t_stack *stack_a, t_array *biggest)
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

void  ft_moves_before_pb(t_stack *stack_a, t_stack *stack_b, t_values *values)
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

void  ft_initialize_values(t_stack *stack_a, t_stack *stack_b, t_cost *result, t_values *values)
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

void  align_stack_b(t_stack *stack_b, int value)
{
  int pos;
  int moves;

  pos = ft_stack_b_pos(stack_b, value);
  if (pos <= stack_b->size / 2)
  {
    moves = pos;
    while (moves-- > 0)
      rb(stack_b);
  }
  else
  {
    moves = stack_b->size - pos;
    while (moves-- > 0)
      rrb(stack_b);
  }
}

int   ft_stack_b_pos(t_stack *stack_b, int value)
{
  int i;

  i = 0;
  if (stack_b->size > 0 && (value > stack_b->arr[i] && value < stack_b->arr[stack_b->size - 1]))
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
int   ft_stack_b_greatest(t_stack *stack_b)
{
  int pos_greatest;
  int i;

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

int check_stack_b_order(t_stack *stack_b)
{
  int i;
  int  biggest_index;
  int current;
  int next;

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

void  stack_b_final_check(t_stack *stack_b)
{
  int seq_b;

  seq_b = check_stack_b_order(stack_b);
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

void  sa(t_stack *stack_a)
{
  int temp;

  temp = stack_a->arr[0];
  stack_a->arr[0] = stack_a->arr[1];
  stack_a->arr[1] = temp;
  ft_printf("sa\n");
}

void  sb(t_stack *stack_b)
{
  int temp;

  temp = stack_b->arr[0];
  stack_b->arr[0] = stack_b->arr[1];
  stack_b->arr[1] = temp;
  ft_printf("sb\n");
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
void  rb(t_stack *stack_b)
{
  int temp;
  int i;

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

void  rrb(t_stack *stack_b)
{
  int temp;
  int i;

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

void  rrr(t_stack *stack_a, t_stack *stack_b)
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

void  pb(t_stack *stack_a, t_stack *stack_b)
{
  int i;

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

