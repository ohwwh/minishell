/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:46:47 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/27 20:05:22 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	strcat(char **dst, const char *src)
{
	const int	s_1 = ft_strlen(*dst);
	const int	s_2 = ft_strlen(src);
	char		*new_str;
	int			i;

	new_str = (char *)malloc((s_1 + s_2) * sizeof(char));
	if (new_str == NULL)
		return ;
	if (new_str != NULL)
	{
		i = 0;
		while (i < s_1)
			new_str[i] = *dst[i++];
	}
	if (src != NULL)
	{
		i = 0;
		while (i < s_2)
			new_str[i + s_1] = src[i++];
		free(*dst);
		*dst = new_str;
	}
}
