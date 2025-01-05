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

size_t	ft_validate_argv(int argc, char **argv);
void	free_split(char **storage);
void	fill_stack_a(t_stack *stack_a, int argc, char **argv);
int		valid_nbr(t_stack *stack_a, long nbr, char	**buf);

#endif
