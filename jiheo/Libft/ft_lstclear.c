/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:15:30 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/11 14:51:16 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*target;
	t_list	*cur;

	if (*lst == NULL)
		return ;
	cur = (*lst)->next;
	target = *lst;
	if (cur == NULL)
		ft_lstdelone(target, del);
	while (cur != NULL)
	{
		ft_lstdelone(target, del);
		target = cur;
		cur = cur->next;
	}
	ft_lstdelone(target, del);
	*lst = NULL;
}
