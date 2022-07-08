/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:46:46 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/09 11:31:12 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_dec_len(t_ll n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*dec_to_str(t_ll n, int sign)
{
	char	*res;
	size_t	len;

	len = get_dec_len(n);
	if (sign == -1)
		len++;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[0] = '0';
	if (sign == -1)
		res[0] = '-';
	res[len] = 0;
	while (n)
	{
		res[--len] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	t_ll	long_n;
	int		sign;

	long_n = (t_ll)n;
	if (long_n >= 0)
		sign = 1;
	else
	{
		sign = -1;
		long_n = (t_ll)sign * long_n;
	}
	res = dec_to_str(long_n, sign);
	return (res);
}
