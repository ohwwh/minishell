/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:36:14 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/27 18:58:26 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *__restrict s1, \
				const char *__restrict s2, size_t n)
{
	size_t	idx;
	size_t	dest_len;

	dest_len = 0;
	idx = 0;
	while (s1[dest_len])
		dest_len++;
	while (s2[idx] && idx + 1 < n)
		s1[dest_len++] = s2[idx++];
	s1[dest_len] = 0;
	return (s1);
}

size_t	ft_strlcat(char *__restrict __dst, \
					const char *__restrict __src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(__dst);
	src_len = ft_strlen(__src);
	if (dest_len >= dstsize)
		return (src_len + dstsize);
	__dst = ft_strncat(__dst, __src, dstsize - dest_len);
	return (src_len + dest_len);
}
