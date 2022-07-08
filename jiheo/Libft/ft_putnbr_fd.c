/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:53:41 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 16:50:02 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_nbr(t_ll n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		print_nbr(-n, fd);
	}
	else if (n / 10 == 0)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
	else
	{
		print_nbr(n / 10, fd);
		c = n % 10 + '0';
		write(fd, &c, 1);
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	print_nbr(n, fd);
}
