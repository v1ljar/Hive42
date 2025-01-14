/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:31:57 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/10 13:36:41 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tp;

	if (!lst)
		return ;
	while (*lst)
	{
		tp = (*lst)->next;
		del(*lst);
		*lst = tp;
	}
	*lst = NULL;
}
