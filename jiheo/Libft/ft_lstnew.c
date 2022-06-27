/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:24:58 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/11 14:51:34 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_ele;

	new_ele = (t_list *)malloc(sizeof(t_list));
	if (new_ele == NULL)
		return (NULL);
	new_ele->content = content;
	new_ele->next = NULL;
	return (new_ele);
}
