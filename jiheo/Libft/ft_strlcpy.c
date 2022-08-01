/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:31:52 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/19 14:39:25 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *__restrict __dst, \
					const char *__restrict __src, size_t dstsize)
{
	size_t	idx;

	idx = 0;
	if (dstsize != 0)
	{
		while (__src[idx] != '\0' && idx < dstsize - 1)
		{
			__dst[idx] = __src[idx];
			idx++;
		}
		__dst[idx] = '\0';
	}
	return (ft_strlen(__src));
}
