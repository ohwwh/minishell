/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:12:47 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 20:10:59 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree.h"

int	find_c(char *src, int from, char c)
{
	while (src[from] && src[from] != c)
	{
		from++;
		if (src[from] == '\'' || src[from] == '"')
			ignore_until_c(src, &from, src[from]);
	}
	return (from);
}
