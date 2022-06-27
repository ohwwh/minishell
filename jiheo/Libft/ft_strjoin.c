/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:54:42 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 16:48:35 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcat(char *s1, const char *s2, size_t s1_len)
{
	size_t	idx;

	idx = 0;
	while (s2[idx])
	{
		s1[s1_len + idx] = s2[idx];
		idx++;
	}
	s1[s1_len + idx] = 0;
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
	{
		if (s1 != NULL)
			return (ft_strdup(s1));
		else if (s2 != NULL)
			return (ft_strdup(s2));
		return (NULL);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[0] = 0;
	ft_strcat(res, s1, 0);
	ft_strcat(res, s2, ft_strlen(res));
	return (res);
}
