/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:38:30 by vuljas            #+#    #+#             */
/*   Updated: 2024/12/14 13:52:28 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./includes/ft_printf.h"

int	validate_array(char **argv, int **arr);

int	main(int argc, char **argv)
{
	int	i;
	int	arr;
	int	size;
	int	*arr;

	if (argc == 1)
		exit;
	i = 1;
	arr = NULL;
	size = validate_array(argv, &arr);
	while (i <= argc)
	{
		ft_printf("%s\n", argv[i]);
		i++;
	}
	return (0);
}

int	validate_array(char **argv, int **arr)
{
	int i;

	i = 0;
	while (argv[])
}