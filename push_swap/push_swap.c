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
void  find_largest_values(t_stack *stack_a, int *largest, int *seclargest, int *thirdlargest);
void  align_stack_b(t_stack *stack_b, int value);
void  stack_b_final_check(t_stack *stack_b);
int   check_stack_b_order(t_stack *stack_b);

int main(int argc, char **argv)
//int	main(void)
{
	size_t		total_args;
	t_stack	stack_a;
  int i;
  //int argc = 6;
  //char *argv[] = {"push_swap", "3", "0", "2", "4", "1"};

	if (argc < 2)
		return(0);
	total_args = ft_validate_argv(argc, argv);
	stack_a.arr = malloc(sizeof(int) * total_args);
	if (!stack_a.arr)
		return (ft_printf("Error\n"), -1);
	stack_a.size = 0;
	fill_stack_a(&stack_a, argc, argv);
  i = 0;
  ft_printf("Original Stack A: ", stack_a.size);
	while (i < stack_a.size)
	{    
		ft_printf("%i ", stack_a.arr[i]);
    if (i + 1 == stack_a.size)
      ft_printf("\n");
		i++;
	}
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
  while (i < stack_a->size)
  {
    if (stack_a->arr[i] < stack_a->arr[i - 1])
      return ;
    i++;
  }
  ft_printf("Sorted!\n");
  /*i = 0;
  ft_printf("Stack A, size: %i\n", stack_a->size);
	while (i < stack_a->size)
	{    
		ft_printf("%i ", stack_a->arr[i]);
    if (!stack_a->arr[i + 1])
      fr_printf("\n");
		i++;
	}*/
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
      seq = stack_a->size - seq;
      while (seq--)
        rra(stack_a);
    }
    else
    {
      while (seq--)
        ra(stack_a);
    }
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
  int largest;
  int seclargest;
  int thirdlargest;

  stack_b.arr = malloc(sizeof(int) * (size_t)(stack_a->size - 3));
  if (!stack_b.arr)
  {
    free(stack_a->arr);
    exit(ft_printf("Error\n"));
  }
  stack_b.size = 0;
  find_largest_values(stack_a, &largest, &seclargest, &thirdlargest);
  ft_printf("Largest: %i\tSecond largest: %i\tThird largest: %i\n", largest, seclargest, thirdlargest);
  while (stack_a->size > 3)
  {
    if (stack_a->arr[0] == largest || stack_a->arr[0] == seclargest || stack_a->arr[0] == thirdlargest)
      ra(stack_a);
    else
    {
      align_stack_b(&stack_b, stack_a->arr[0]);
      pb(stack_a, &stack_b);
    }
  }
  stack_b_final_check(&stack_b);
  sort_three(stack_a);
  while (stack_b.size > 0)
    pa(stack_a, &stack_b);
	free(stack_b.arr);
}

void  align_stack_b(t_stack *stack_b, int value)
{
  int pos;
  int moves;

  pos = 0;
  while ((pos < stack_b->size && stack_b->arr[pos] < value) || (stack_b->arr[pos] - value < stack_b->arr[pos + 1] - value))
    pos++;
  if (pos == 0 || pos == stack_b->size)
    return ;
  ft_printf("HERE, pos: %i\n", pos);
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
    if (stack_b->arr[i] < stack_b->arr[biggest_index])
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
  ft_printf("smallest element: %i", seq_b);
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

void  find_largest_values(t_stack *stack_a, int *largest, int *seclargest, int *thirdlargest)
{
  int i;

  i = 0;
  *largest = INT_MIN;
  *seclargest = INT_MIN;
  *thirdlargest = INT_MIN;
  while (i < stack_a->size)
  {
    if (stack_a->arr[i] > *largest)
    {
      *thirdlargest = *seclargest;
      *seclargest = *largest; 
      *largest = stack_a->arr[i];
      
    }
    else if (stack_a->arr[i] > *seclargest)
    {
      *thirdlargest = *seclargest;
      *seclargest = stack_a->arr[i];
    }
    else if (stack_a->arr[i] > *thirdlargest)
      *thirdlargest = stack_a->arr[i];
    i++;
  }
}

void  sa(t_stack *stack_a)
{
  int temp;
  int i;

  temp = stack_a->arr[0];
  stack_a->arr[0] = stack_a->arr[1];
  stack_a->arr[1] = temp;
  i = 0;
  ft_printf("Stack A after sa: ");
	while (i < stack_a->size)
	{    
		ft_printf("%i ", stack_a->arr[i]);
    if (!stack_a->arr[i + 1])
      ft_printf("\n");
		i++;
	}
  ft_printf("sa\n");
}

void  sb(t_stack *stack_b)
{
  int temp;
  int i;

  temp = stack_b->arr[0];
  stack_b->arr[0] = stack_b->arr[1];
  stack_b->arr[1] = temp;
  i = 0;
  ft_printf("Stack B after sb: ");
	while (i < stack_b->size)
	{    
		ft_printf("%i ", stack_b->arr[i]);
    if (i + 1 == stack_b->size)
      ft_printf("\n");
		i++;
	}
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
  i = 0;
  ft_printf("Stack A after ra: ");
	while (i < stack_a->size)
	{    
		ft_printf("%i ", stack_a->arr[i]);
    if (!stack_a->arr[i + 1])
      ft_printf("\n");
		i++;
	}
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
  i = 0;
  ft_printf("Stack B after rb: ");
	while (i < stack_b->size)
	{    
		ft_printf("%i ", stack_b->arr[i]);
    if (!stack_b->arr[i + 1])
      ft_printf("\n");
		i++;
	}
  ft_printf("rb\n");
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
  i = 0;
  ft_printf("Stack A after rra: ");
	while (i < stack_a->size)
	{    
		ft_printf("%i ", stack_a->arr[i]);
    if (!stack_a->arr[i + 1])
      ft_printf("\n");
		i++;
	}
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
  i = 0;
  ft_printf("Stack B after rrb: ");
	while (i < stack_b->size)
	{    
		ft_printf("%i ", stack_b->arr[i]);
    if (!stack_b->arr[i + 1])
      ft_printf("\n");
		i++;
	}
  ft_printf("rrb\n");
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
  i = 0;
  ft_printf("Stack A after pb: ", stack_a->size);
	while (i < stack_a->size)
	{    
		ft_printf("%i ", stack_a->arr[i]);
    if (i + 1 == stack_a->size)
      ft_printf("\n");
		i++;
	}
  i = 0;
  ft_printf("Stack B after pb: ", stack_b->size);
	while (i < stack_b->size)
	{    
		ft_printf("%i ", stack_b->arr[i]);
    if (i + 1 == stack_b->size)
      ft_printf("\n");
		i++;
	}
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
  i = 0;
  ft_printf("Stack A after pa: ", stack_a->size);
	while (i < stack_a->size)
	{    
		ft_printf("%i ", stack_a->arr[i]);
    if (i + 1 == stack_a->size)
      ft_printf("\n");
		i++;
	}
  i = 0;
  ft_printf("Stack B after pa: ", stack_b->size);
	while (i < stack_b->size)
	{    
		ft_printf("%i ", stack_b->arr[i]);
    if (i + 1 == stack_b->size)
      ft_printf("\n");
		i++;
	}
  ft_printf("pa\n");
}

