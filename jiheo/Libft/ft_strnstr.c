/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:28:43 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/08 09:20:27 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_same_str(const char *haystack, \
						const char *needle, size_t cur_idx)
{
	size_t	idx;

	idx = 0;
	while (needle[++idx])
	{
		if (needle[idx] != haystack[++cur_idx])
			return (0);
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if (*needle == 0)
		return ((char *)haystack);
	if (*haystack == 0)
		return (NULL);
	i = 0;
	needle_len = ft_strlen(needle);
	while (haystack[i] && i + needle_len <= len)
	{
		if (haystack[i] == needle[0] && is_same_str(haystack, needle, i))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
