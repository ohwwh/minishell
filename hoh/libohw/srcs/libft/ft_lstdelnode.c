/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:43:46 by ohw               #+#    #+#             */
/*   Updated: 2021/11/30 20:18:59 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelnode(t_list **lst, t_list *target, void (*del)(void *))
{
	t_list	*delnode;
	t_list	*prev;

	prev = 0;
	delnode = *lst;
	while (delnode)
	{
		if (delnode == target)
		{
			if (prev)
				prev->next = delnode->next;
			else
				*lst = delnode->next;
			del(delnode -> content);
			free(delnode);
			break ;
		}
		prev = delnode;
		delnode = delnode->next;
	}
}