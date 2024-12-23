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

void  check_stack_order(t_stack *stack_a);
void  sort_stack(t_stack *stack_a);
void  sort_two(t_stack *stack_a);
void  sort_three(t_stack *stack_a);
void  sort_rest(t_stack *stack_a);
void  sa(t_stack *stack_a);
void  ra(t_stack *stack_a);
void  rra(t_stack *stack_a);
void  pb(t_stack *stack_a, t_stack *stack_b);

int	main(int argc, char **argv)
{
	int		total_args;
	t_stack	stack_a;
	int		i;

	if (argc < 2)
		exit(0);
	total_args = ft_validate_argv(argc, argv);
	stack_a.arr = malloc(sizeof(int) * total_args);
	if (!stack_a.arr)
		return (ft_printf("Error\n"), -1);
	stack_a.size = 0;
	fill_stack_a(&stack_a, argc, argv);
  check_stack_order(&stack_a);
  sort_stack(&stack_a);
  check_stack_order(&stack_a);
	i = 0;
	while (i < stack_a.size)
	{
		ft_printf("%i\n", stack_a.arr[i]);
		i++;
	}
	free(stack_a.arr);
	return (0);
}

void check_stack_order(t_stack *stack_a)
{
  int i;

  i = 1;
  while (i < stack_a->size)
  {
    if (stack_a->arr[i] < stack_a->arr[i - 1])
      return ;
    i++;
  }
  ft_printf("Sorted!\n");
  exit(0);
}

void  sort_stack(t_stack *stack_a)
{
  if (stack_a->size == 2)
    sort_two(stack_a);
  else if (stack_a->size == 3)
    sort_three(stack_a);
  else
    sort_rest(stack_a);
}

void  sort_two(t_stack *stack_a)
{
  if (stack_a->arr[0] > stack_a->arr[1])
    sa(stack_a);
}

void  sort_three(t_stack *stack_a)
{
  if (stack_a->arr[0] > stack_a->arr[1] && stack_a->arr[0] < stack_a->arr[2])
    sa(stack_a);
  else if (stack_a->arr[0] > stack_a->arr[1] && stack_a->arr[1] > stack_a->arr[2])
  {
    ra(stack_a);
    sa(stack_a);
  }
  else if (stack_a->arr[0] < stack_a->arr[1] && stack_a->arr[1] > stack_a->arr[2]
    && stack_a->arr[0] < stack_a->arr[2])
  {
    sa(stack_a);
    ra(stack_a);
  }
  else if (stack_a->arr[0] < stack_a->arr[1] && stack_a->arr[1] > stack_a->arr[2])
    rra(stack_a);
  else if (stack_a->arr[0] > stack_a->arr[1] && stack_a->arr[1] < stack_a->arr[2])
    ra(stack_a);
}

void  sort_rest(t_stack *stack_a)
{
  t_stack stack_b;

  stack_b.arr = malloc(sizeof(int) * 1);
  if (!stack_b.arr)
  {
    free(stack_a->arr);
    exit(ft_printf("Error\n"));
  }
  ft_printf("HERE\n");
  stack_b.size = 0;
  while (stack_a->size > 3)
  {
    if (stack_a->arr[0] < stack_a->arr[1] && stack_a->arr[0] < stack_a->arr[stack_a->size - 1])
    {
      pb(stack_a, &stack_b);
      stack_a->size--;
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

void  ra(t_stack *stack_a)
{
  int temp;
  int i;

  temp = stack_a->arr[0];
  i = 0;
  while (i < (stack_a->size) - 1)
  {
    stack_a->arr[i] = stack_a->arr[i + 1];
    i++;
  }
  stack_a->arr[(stack_a->size) - 1] = temp;
  ft_printf("ra\n");
}

void  rra(t_stack *stack_a)
{
  int temp;
  int i;

  temp = stack_a->arr[2];
  i = 0;
  while (i < (stack_a->size) -1)
  {
    stack_a->arr[stack_a->size - i] = stack_a->arr[stack_a->size - i - 1];
    i++; 
  }
  stack_a->arr[0] = temp;
  ft_printf("rra\n");
}

void  pb(t_stack *stack_a, t_stack *stack_b)
{
  int temp;
  int i;
  int temp_arr[stack_b->size + 1];

  temp = stack_a->arr[0];
  i = 0;
  while (i < stack_a->size - 1)
  {
    stack_a->arr[i] = stack_a->arr[i + 1];
    i++;
  }
  stack_a->size--;
  if (stack_b->size == 0)
    stack_b->arr[0] = temp;
  else
  {
    temp_arr[0] = temp;
    i = 1;
    while (i < stack_b->size)
    {
      temp_arr[i] = stack_b->arr[i - 1];
      i++;
    }
    free(stack_b->arr);
    stack_b->arr = malloc(sizeof(int) * stack_b->size + 1);
    if (!stack_b->arr)
		{
			free(stack_b->arr);
			ft_printf("Error filling stack_b!\n");
			exit(-1);
		}
    i = 0;
    while (i < stack_b->size)
    {
      stack_b->arr[i] = temp_arr[i];
      i++;
    }
  }
  stack_b->size++;
  ft_printf("pb\n");
}
