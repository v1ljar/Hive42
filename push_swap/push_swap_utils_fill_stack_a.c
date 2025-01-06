/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:39:29 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/05 12:39:40 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		if (!storage)
		{
			ft_free_split(storage);
			ft_printf("Error\n");
			return (-1);
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
			ft_printf("Error filling stack_a!\n");
			exit(-1);
		}
		j = 0;
		while (buf[j] && ft_valid_nbr(stack_a, ft_atoi(buf[j]), buf))
		{
			stack_a->arr[stack_a->size++] = (int)ft_atoi(buf[j]);
			j++;
		}
		ft_free_split(buf);
		i++;
	}
}

int	ft_valid_nbr(t_stack *stack_a, long nbr, char	**buf)
{
	int	i;

	i = 0;
	while (stack_a->arr[i])
	{
		if (stack_a->arr[i] == nbr || nbr < INT_MIN || nbr > INT_MAX)
		{			
			free(stack_a->arr);
			ft_free_split(buf);
			exit(ft_printf("Error\n"));
		}
		i++;
	}
	return (1);
}
