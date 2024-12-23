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
void  sa(t_stack *stack_a);
void  ra(t_stack *stack_a);
void  rra(t_stack *stack_a);

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

