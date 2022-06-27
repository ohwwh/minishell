/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:04:44 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 16:53:30 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (true);
		set++;
	}
	return (false);
}

static char	*find_res(const char *s1, const char *set, size_t s, size_t e)
{
	size_t	len;

	while (e > 0 && s1[e])
	{
		if (!is_set(s1[e], set))
			break ;
		e--;
	}
	len = e - s + 1;
	return (ft_substr(s1, s, len));
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start_idx;
	size_t	end_idx;
	size_t	len;

	if (set == NULL && s1 != NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	start_idx = 0;
	end_idx = len - 1;
	while (start_idx < len && s1[start_idx])
	{
		if (!is_set(s1[start_idx], set))
			break ;
		start_idx++;
	}
	if (s1[start_idx] == 0)
		return (ft_strdup(""));
	return (find_res(s1, set, start_idx, end_idx));
}
