/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_fill_stack_a.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:39:29 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/07 17:32:32 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_validate_buf(char **buf, t_stack *stack_a);

size_t	ft_validate_argv(int argc, char **argv)
{
	char	**storage;
	size_t	res;
	int		i;
	int		j;

	res = 0;
	i = 1;
	while (i < argc)
	{
		storage = ft_split(argv[i], ' ');
		if (!storage || *storage == NULL)
		{
			ft_free_split(storage);
			exit(write(2, "Error\n", 6));
		}
		j = 0;
		while (storage[j++])
			res++;
		ft_free_split(storage);
		i++;
	}
	return (res);
}

void	ft_free_split(char **storage)
{
	int	i;

	i = 0;
	while (storage[i])
		free(storage[i++]);
	free(storage);
}

void	ft_fill_stack_a(t_stack *stack_a, int argc, char **argv)
{
	char	**buf;
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		buf = ft_split(argv[i], ' ');
		if (!buf)
		{
			ft_free_split(buf);
			exit(write(2, "Error\n", 6));
		}
		ft_validate_buf(buf, stack_a);
		j = 0;
		while (buf[j] && ft_valid_nbr(stack_a, ft_atoi(buf[j]), buf))
		{
			stack_a->arr[stack_a->size] = (int)ft_atoi(buf[j]);
			stack_a->size++;
			j++;
		}
		ft_free_split(buf);
		i++;
	}
}

static void	ft_validate_buf(char **buf, t_stack *stack_a)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i] != NULL)
	{
		j = 0;
		if (buf[i][0] == '+' || buf[i][0] == '-')
		{
			if (buf[i][1] < '0' || buf[i][1] > '9')
				ft_free_and_exit(buf, stack_a);
			j++;
		}		
		while (buf[i][j] != '\0')
		{			
			if (buf[i][j] < '0' || buf[i][j] > '9')
				ft_free_and_exit(buf, stack_a);
			j++;
		}
		i++;
	}
}

int	ft_valid_nbr(t_stack *stack_a, long nbr, char	**buf)
{
	int	i;

	i = 0;
	while (i < stack_a->size || nbr < INT_MIN || nbr > INT_MAX)
	{
		if (stack_a->arr[i] == nbr || nbr < INT_MIN || nbr > INT_MAX)
		{
			free(stack_a->arr);
			ft_free_split(buf);
			exit(write(2, "Error\n", 6));
		}
		i++;
	}
	return (1);
}
