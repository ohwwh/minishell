/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:09:07 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/27 19:51:19 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*get_env(const char *key)
{
	int	i;

	i = 0;
	while (g_envs[i].key)
	{
		if (ft_strncmp(g_envs[i].key, key, ft_strlen(key)) == 0)
			return (g_envs[i].value);
		i++;
	}
	return (NULL);
}
