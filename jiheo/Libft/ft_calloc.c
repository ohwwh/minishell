/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:47:58 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 17:26:42 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	idx;
	size_t	s;

	idx = 0;
	s = size * count;
	res = malloc(s);
	if (res == NULL)
		return (NULL);
	while (s--)
		*((t_uchar *)res + s) = 0;
	return (res);
}
