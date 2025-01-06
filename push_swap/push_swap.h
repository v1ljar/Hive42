/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:46:57 by vuljas            #+#    #+#             */
/*   Updated: 2024/12/23 15:50:56 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int	*arr;
	int	size;
}	t_stack;

typedef struct s_cost
{
	int	a_cost;
	int	b_cost;
	int	total;
}	t_cost;

typedef struct s_array
{
	int	largest;
	int	sec;
	int	third;
}	t_array;

typedef struct s_values
{
	int ra_v;
	int rb_v;
	int rra_v;
	int rrb_v;
}	t_values;

void  ft_sort_stack(t_stack *stack_a);
// Fill stack a
size_t	ft_validate_argv(int argc, char **argv);
void	ft_free_split(char **storage);
void	ft_fill_stack_a(t_stack *stack_a, int argc, char **argv);
int		ft_valid_nbr(t_stack *stack_a, long nbr, char	**buf);
// Check stack
void  ft_check_stack_completed(t_stack *stack_a);
int   ft_check_stack_order(t_stack *stack_a);
void  ft_stack_b_final_check(t_stack *stack_b);
int   ft_check_stack_b_order(t_stack *stack_b);
// Sort
void  ft_find_largest_values(t_stack *stack_a, t_array *biggest);
void  ft_calculate_cost(t_stack *stack_a,t_stack *stack_b, t_array *biggest);
// Sort make moves
void  ft_make_moves(t_cost *result, t_stack *stack_a, t_stack *stack_b);
// Sort b pos
int   ft_stack_b_pos(t_stack *stack_b, int value);
// A moves
void  sa(t_stack *stack_a);
void  ra(t_stack *stack_a);
void  rra(t_stack *stack_a);
void  pa(t_stack *stack_a, t_stack *stack_b);
void  rr(t_stack *stack_a, t_stack *stack_b);
// B moves
void  sb(t_stack *stack_b);
void  rb(t_stack *stack_a);
void  rrb(t_stack *stack_b);
void  pb(t_stack *stack_a, t_stack *stack_b);
void  rrr(t_stack *stack_a, t_stack *stack_b);

#endif
