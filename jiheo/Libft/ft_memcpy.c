/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:15:18 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 14:40:49 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *__restrict __dst, \
					const void *__restrict __src, size_t n)
{
	size_t			i;
	t_uchar			*dst_tmp;
	const t_uchar	*src_tmp = __src;

	i = 0;
	dst_tmp = __dst;
	if (__dst || __src)
	{
		while (i < n)
		{
			dst_tmp[i] = src_tmp[i];
			i++;
		}
	}
	return (__dst);
}
