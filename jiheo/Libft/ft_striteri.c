/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:47:41 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 16:55:55 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	len;
	size_t	idx;

	if (s == NULL || f == NULL)
		return ;
	len = ft_strlen(s);
	idx = 0;
	while (idx < len)
	{
		f(idx, &s[idx]);
		idx++;
	}
}
