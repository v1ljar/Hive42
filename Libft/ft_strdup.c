/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:27:07 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 16:13:41 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*result;

	len = ft_strlen(s);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main()
{
	char	str[] = "This is the string to duplicate";
	char	*res;

	res = ft_strdup(str);
	if (res)
		printf("Duplication sucessful! %s\n", res);
	else
		printf("Duplication failed!\n");
	free(res);
	return (0);
}
*/
