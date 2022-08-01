/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:17:40 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 11:39:03 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;
	t_uchar	temp1;
	t_uchar	temp2;

	idx = 0;
	if (n == 0)
		return (0);
	temp1 = (t_uchar)s1[idx];
	temp2 = (t_uchar)s2[idx];
	while (s1[idx] && s2[idx] && idx + 1 < n)
	{
		if (temp1 != temp2)
			return (temp1 - temp2);
		idx++;
		temp1 = (t_uchar)s1[idx];
		temp2 = (t_uchar)s2[idx];
	}
	return (temp1 - temp2);
}
