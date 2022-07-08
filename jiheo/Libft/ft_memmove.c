/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:16:04 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 14:43:05 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*res;
	size_t	i;

	res = dst;
	if (dst || src)
	{
		if (dst <= src)
		{
			i = 0;
			while (i < len)
			{
				((char *)dst)[i] = ((char *)src)[i];
				i++;
			}
		}
		else
		{
			i = len;
			while (i--)
				((char *)dst)[i] = ((char *)src)[i];
		}
	}
	return (dst);
}
